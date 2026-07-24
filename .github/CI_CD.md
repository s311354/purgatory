# CI/CD Guide

This project uses three GitHub Actions workflows:

| Workflow | Purpose | Main output |
| --- | --- | --- |
| `CI` | Build, unit tests, sample run, code quality, and documentation checks | Linux executable artifact |
| `Code Coverage` | Exercise the sample program with GCC coverage instrumentation | HTML coverage report |
| `Release` | Build and publish a tagged Linux release | Binary archive and SHA-256 checksum |

The workflow definitions in `.github/workflows/` are the source of truth. This guide documents their current behavior and the corresponding local commands.

## CI

File: [workflows/ci.yml](workflows/ci.yml)

Triggers:

- Pushes to `main` or `develop`
- Pull requests targeting `main` or `develop`
- Manual `workflow_dispatch`

### Build and Test

The `build-and-test` job runs on Ubuntu 22.04 with GCC 11 and Ninja:

1. Checks out the repository and the pinned GoogleTest submodule.
2. Configures a C++17 Release build with `BUILD_TESTING=ON`.
3. Builds the executable and unit-test target.
4. Runs every test discovered by CTest.
5. Runs `purgatory` with `src/test.txt`.
6. Uploads `build/purgatory` as `purgatory-binary` for seven days.

A failing configure, build, unit test, or sample run fails the job.

### Code Quality

The `code-quality` job installs clang-format 14 and cppcheck.

- **cppcheck** performs static analysis on `src/` with `--enable=warning,style,performance,portability` and will fail the build if issues are found (`--error-exitcode=1`). The check automatically suppresses:
  - `functionStatic` - Intentional class-based design pattern
  - `useStlAlgorithm` - Educational emphasis on explicit implementations
  - `noExplicitConstructor` - Query class requires implicit conversion
- **clang-format** checks all tracked files with common C and C++ extensions. Formatting differences fail the job.
- The committed `.clang-format` file defines the LLVM-based repository style.
- The cppcheck report is uploaded as an artifact and retained for 30 days.

The formatting check uses tracked files rather than scanning dependency or build directories, so the GoogleTest submodule and generated sources are excluded.

### Documentation

The `documentation` job:

- Verifies that `README.md`, `LICENSE`, `docs/ALGORITHMS.md`, and `tmux-session.sh` exist.
- Runs Lychee against root and `docs/` Markdown files.

Broken-link reporting is currently non-blocking because the action has `continue-on-error: true`.

## Code Coverage

File: [workflows/coverage.yml](workflows/coverage.yml)

Triggers:

- Pushes to `main` or `develop`
- Pull requests targeting `main`
- Manual `workflow_dispatch`

The coverage job runs on Ubuntu 22.04 with GCC 11, Ninja, and gcovr. It:

1. Configures a Debug build with GCC coverage flags and `BUILD_TESTING=OFF`.
2. Builds and runs `purgatory` with `src/test.txt`.
3. Generates `coverage.html` and detailed HTML pages.
4. Excludes `src/main.cc` and `src/entry.cc` from the report.
5. Uploads `coverage*.html` as `coverage-report` for 30 days.
6. Prints a text summary in the workflow log.

This is sample-program coverage, not unit-test coverage. Report generation and upload are intentionally non-blocking, and there is currently no minimum coverage threshold.

## Release

File: [workflows/release.yml](workflows/release.yml)

Triggers:

- Tags matching `v*.*.*`
- Manual `workflow_dispatch` with a required tag value

The release job runs on Ubuntu 22.04 and:

1. Checks out full Git history for changelog generation.
2. Builds a Release binary with GCC 11, Ninja, and `BUILD_TESTING=OFF`.
3. Runs the binary with `src/test.txt`.
4. Packages the binary, `README.md`, `LICENSE`, and `docs/`.
5. Produces `purgatory-linux-x86_64.tar.gz` and its SHA-256 checksum.
6. Generates a changelog from commits since the previous tag.
7. Publishes a non-draft GitHub release with both files attached.

The workflow uses the automatically provided `GITHUB_TOKEN` with `contents: write`. No additional repository secret is required.

## Reproduce CI Locally

### Prerequisites

- CMake 3.14 or later
- GCC 11 or another C++17 compiler
- Ninja
- Git
- clang-format 14
- cppcheck

Clone with the pinned test dependency:

```bash
git clone --recurse-submodules https://github.com/s311354/purgatory.git
cd purgatory
```

For an existing clone:

```bash
git submodule sync --recursive
git submodule update --init --recursive
```

### Build and Unit Tests

```bash
cmake -S . -B build \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=g++-11 \
  -DBUILD_TESTING=ON

cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/purgatory src/test.txt
```

If `g++-11` is unavailable, use another C++17 compiler such as `c++` or `clang++`.

### Static Analysis

Run the same cppcheck checks as CI:

```bash
cppcheck \
  --enable=warning,style,performance,portability \
  --std=c++17 \
  --error-exitcode=1 \
  --inline-suppr \
  --suppress=missingIncludeSystem \
  --suppress=functionStatic \
  --suppress=useStlAlgorithm \
  --suppress=noExplicitConstructor:src/query.h:79 \
  --quiet \
  src/
```

Or use the provided script:

```bash
./cppcheck.sh strict   # Same checks as CI (includes portability)
./cppcheck.sh check    # Standard checks (warnings + style + performance)
./cppcheck.sh report   # Generate detailed report
```

### Formatting

Check formatting:

```bash
git ls-files -z -- \
  '*.c' '*.cc' '*.cpp' '*.cxx' \
  '*.h' '*.hh' '*.hpp' '*.hxx' | \
  xargs -0 clang-format-14 --style=file --dry-run --Werror
```

Apply formatting:

```bash
git ls-files -z -- \
  '*.c' '*.cc' '*.cpp' '*.cxx' \
  '*.h' '*.hh' '*.hpp' '*.hxx' | \
  xargs -0 clang-format-14 --style=file -i
```

### Coverage

```bash
cmake -S . -B build-coverage \
  -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=g++-11 \
  -DCMAKE_CXX_FLAGS=--coverage \
  -DCMAKE_EXE_LINKER_FLAGS=--coverage \
  -DBUILD_TESTING=OFF

cmake --build build-coverage --parallel
./build-coverage/purgatory src/test.txt

gcovr --root . \
  --filter src/ \
  --exclude 'src/main.cc' \
  --exclude 'src/entry.cc' \
  --html-details coverage.html \
  --print-summary
```

## Creating a Release

For the normal tag-driven path:

```bash
git tag -a v1.0.0 -m "Release v1.0.0"
git push origin v1.0.0
```

Alternatively, open **Actions → Release → Run workflow** and supply a tag such as `v1.0.0`.

The current workflow publishes only a Linux x86-64 archive. It does not build macOS, ARM64, or Windows artifacts.

## Troubleshooting

### GoogleTest directory is empty

The dependency is a Git submodule. Restore it with:

```bash
git submodule sync --recursive
git submodule update --init --recursive
test -f third-party/googletest/CMakeLists.txt
```

When cloning a fresh checkout, use `git clone --recurse-submodules`.

### CMake cannot find Ninja

Install Ninja or omit `-G Ninja` to use CMake's default generator.

### Compiler rejects `std::string_view`

Use a compiler with C++17 support and do not override the project with an older `CMAKE_CXX_STANDARD`.

### Formatting fails in CI

Run the formatting apply command above with clang-format 14, then rerun the dry-run check. A different clang-format major version can produce a different result.

### Tests pass locally but fail in CI

- Reconfigure from a clean build directory.
- Use a Release build with GCC 11 when reproducing CI exactly.
- Confirm the GoogleTest submodule is at the recorded commit with `git submodule status`.
- Run `ctest --test-dir build --output-on-failure` to show the failing assertion.

### Release creation fails

- Confirm the tag matches `v*.*.*`.
- Confirm `README.md`, `LICENSE`, and `docs/` exist.
- Confirm the workflow has `contents: write`.
- For manual runs, ensure the supplied tag is the intended release tag.
