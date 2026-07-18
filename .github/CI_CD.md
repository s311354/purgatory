# CI/CD Documentation

This document describes the continuous integration and deployment pipeline for the purgatory project.

## Overview

The CI/CD pipeline consists of 4 main workflows:

1. **CI (Continuous Integration)** - Main build and test pipeline
2. **Release** - Automated release builds and publishing
3. **Code Coverage** - Test coverage analysis and reporting
4. **Pull Request Checks** - Automated PR validation

## Workflows

### 1. CI Workflow (`.github/workflows/ci.yml`)

**Triggers:**
- Push to `main` or `develop` branches
- Pull requests to `main` or `develop`
- Manual dispatch

**Jobs:**

#### build-and-test
Tests on multiple configurations:
- **Operating Systems:** Ubuntu 22.04, Ubuntu 20.04
- **Compilers:** g++-10, g++-11, clang++-12, clang++-14
- **Build Types:** Release, Debug

**Steps:**
1. Checkout code with submodules
2. Install dependencies (CMake, Ninja, compiler)
3. Configure CMake with specified compiler and build type
4. Build with Ninja
5. Run CTest suite
6. Test executable with sample input
7. Upload artifacts (Release builds only)

#### sanitizers
Runs AddressSanitizer (ASan) and ThreadSanitizer (TSan) checks:
- Detects memory leaks, buffer overflows, use-after-free
- Identifies data races and threading issues

#### code-quality
Performs static analysis:
- **cppcheck** - Static code analysis
- **clang-format** - Code style verification
- Build with `-Wall -Wextra -Wpedantic`

#### documentation
Validates documentation:
- Checks all documentation files exist
- Validates markdown links with lychee (fast Rust-based checker)
- Ensures tmux configuration is present

#### performance
Performance benchmarks:
- Measures test execution time
- Runs Valgrind for memory leak detection
- Performance regression detection

#### cross-platform
Tests on macOS:
- macOS 13 (Intel)
- macOS 14 (Apple Silicon)

### 2. Release Workflow (`.github/workflows/release.yml`)

**Triggers:**
- Push tags matching `v*.*.*` (e.g., v1.0.0)
- Manual dispatch with tag input

**Jobs:**

#### build-release
Builds release artifacts for multiple platforms in parallel:
- Linux x86_64
- Linux ARM64  
- macOS x86_64 (Intel)
- macOS ARM64 (Apple Silicon)

**Steps for each platform:**
1. Checkout code with submodules
2. Install dependencies (CMake, Ninja, compiler)
3. Configure and build in Release mode
4. Run full test suite
5. Package artifacts with documentation
6. Generate checksums (SHA256)
7. Upload as GitHub artifacts

#### create-release
Creates the GitHub release after all builds complete:
1. Downloads all platform artifacts
2. Generates changelog from git commits
3. Creates GitHub release using modern gh-release action
4. Attaches all platform binaries and checksums

**Artifacts include:**
- Binary executable
- Documentation (README, docs/)
- LICENSE file
- SHA256 checksums

### 3. Code Coverage Workflow (`.github/workflows/coverage.yml`)

**Triggers:**
- Push to `main` or `develop`
- Pull requests to `main`

**Steps:**
1. Build with coverage flags (`--coverage`)
2. Run all tests
3. Generate coverage report with gcovr
4. Upload to Codecov
5. Create HTML coverage report
6. Comment coverage summary on PRs

**Coverage excludes:**
- `src/main.cc` (sandbox file)
- `src/entry.cc` (entry point)
- Test code itself

### 4. Pull Request Checks (`.github/workflows/pr-checks.yml`)

**Triggers:**
- PR opened, synchronized, or reopened

**Jobs:**

#### pr-info
Provides PR statistics:
- Number of changed files
- Lines added/removed
- File change status
- Breaking change detection

#### size-check
Compares binary size:
- Builds both PR and base branch
- Reports size difference
- Warns if binary grows >1MB

#### test-algorithms
Analyzes test coverage:
- Counts total/passed/failed tests
- Reports failed test details
- Uploads test output as artifact

## Status Badges

Add these to your README.md:

```markdown
![CI](https://github.com/s311354/purgatory/workflows/CI/badge.svg)
![Release](https://github.com/s311354/purgatory/workflows/Release/badge.svg)
![Code Coverage](https://github.com/s311354/purgatory/workflows/Code%20Coverage/badge.svg)
```

## Local Testing

Before pushing, you can test locally:

```bash
# Run the same build as CI
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_COMPILER=g++-11 \
  -DBUILD_TESTING=ON \
  -B build

cmake --build build -j$(nproc)
cd build && ctest --output-on-failure
```

### Comprehensive Testing (formerly nightly build)

For thorough testing across multiple configurations:

```bash
# Test multiple build types
for build_type in Debug Release RelWithDebInfo; do
  echo "Testing $build_type..."
  cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=$build_type \
    -DCMAKE_CXX_COMPILER=g++-11 \
    -DBUILD_TESTING=ON \
    -B build-$build_type
  
  cmake --build build-$build_type -j$(nproc)
  cd build-$build_type && ctest --output-on-failure
  cd ..
done
```

### Stress Testing

```bash
# Run tests multiple times for stability
for i in {1..10}; do
  echo "=== Iteration $i ==="
  cd build && ctest --output-on-failure || exit 1
  cd .. && ./build/purgatory src/test.txt || exit 1
done
```

### C++ Standard Compatibility Testing

```bash
# Test different C++ standards
for std in 11 14 17 20; do
  echo "Testing C++$std..."
  cmake -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_CXX_COMPILER=g++-11 \
    -DCMAKE_CXX_STANDARD=$std \
    -DBUILD_TESTING=ON \
    -B build-cpp$std
  
  cmake --build build-cpp$std -j$(nproc)
  cd build-cpp$std && ctest --output-on-failure
  cd ..
done
```

### Test with sanitizers:

```bash
# AddressSanitizer
cmake -DPURGATORY_USE_ASAN=ON -DBUILD_TESTING=ON -B build-asan
cmake --build build-asan -j$(nproc)
cd build-asan && ctest --output-on-failure

# ThreadSanitizer
cmake -DPURGATORY_USE_TSAN=ON -DBUILD_TESTING=ON -B build-tsan
cmake --build build-tsan -j$(nproc)
cd build-tsan && ctest --output-on-failure
```

### Check code quality:

```bash
# Static analysis
cppcheck --enable=all src/*.cc

# Format check
clang-format -style=file --dry-run src/*.cc test/*.cc
```

## Creating a Release

1. **Tag the release:**
   ```bash
   git tag -a v1.0.0 -m "Release version 1.0.0"
   git push origin v1.0.0
   ```

2. **Workflow automatically:**
   - Creates GitHub release
   - Generates changelog
   - Builds for all platforms
   - Uploads artifacts with checksums

3. **Manual release (if needed):**
   - Go to Actions → Release → Run workflow
   - Enter tag name (e.g., v1.0.0)

## Secrets Configuration

No secrets required for basic CI/CD. The workflows use `GITHUB_TOKEN` which is automatically provided.

Optional secrets for enhanced features:
- `CODECOV_TOKEN` - For Codecov integration (optional)

## Troubleshooting

### Build fails on specific compiler
Check the build matrix in `ci.yml` and ensure the compiler is properly installed.

### Tests fail only in CI
- Check for race conditions (run with TSan)
- Verify file paths are relative
- Ensure no hardcoded system dependencies

### Coverage report not uploading
Codecov integration is optional and continues on error. Check Codecov token if needed.

### Need comprehensive testing
Since nightly builds are no longer automated, use manual workflow dispatch:
- Go to Actions → CI → Run workflow
- Or run comprehensive tests locally (see Local Testing section)

### Running coverage on-demand
Coverage runs automatically on pushes and PRs. For manual coverage:
- Go to Actions → Code Coverage → Run workflow

### Release workflow fails
- Verify tag format matches `v*.*.*`
- Check that all required files exist (LICENSE, docs/, etc.)
- Ensure permissions are set for `contents: write`

## Performance Considerations

**Build time optimization:**
- Uses Ninja generator (faster than Make)
- Parallel builds with `-j$(nproc)`
- Caches between workflow runs (implicit by GitHub)

**Test optimization:**
- Parallel test execution with CTest
- Selective test matrix (excludes some combinations)

## Contributing

When adding new features:

1. **Update tests** - Ensure new code has test coverage
2. **Run sanitizers** - Test with ASan and TSan locally
3. **Check documentation** - Update docs if adding new algorithms
4. **Verify CI passes** - All checks must pass before merge

## Continuous Improvement

Planned enhancements:
- [ ] Docker container builds
- [ ] Static binary releases
- [ ] Benchmark regression tracking
- [ ] Automated dependency updates
- [ ] Security scanning (CodeQL)
- [ ] Performance profiling reports

## Contact

For CI/CD issues, please open an issue with the `ci/cd` label.
