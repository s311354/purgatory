# purgatory: Structured Coding Sandbox for interview Prep and Testing

purgatory is a lightweight, modular C++11-based environment for prototyping, embedded experimentation, and test-driven workflows.

## Porject Layout

```shell
.
├── CMakeLists.txt         # Root CMake configuration
├── install-build-deps.sh  # script to install compiler/tools
├── src/
│   ├── main.cc            # Sandbox for quick experiments 
│   ├── entry.cc           # Entry point or application driver
│   ├── array.cc           # Algorithm implementation
│   └── purgatory.h        # Shared header/interfaces
├── test/
│   ├── CMakeLists.txt     # CMake config for test targets
│   ├── test.cc            # GoogleTest unit tests
└── third-party
    └── googletest/        # Embedded gtest framework
```

## How to Build

purgatory is written in C++11, so if you build purgatory yourself, you will need a recent version of a C++ compiler and a C++ standard library. We recommend GCC 10.2 or Clang 12.0.0 (or later).

### Compile purgatory

```shell
git clone https://github.com/s311354/purgatory.git
cd purgatory
./install-build-deps.sh
cmake -DCAMKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -B build
cmake --build build -j$(nproc)
```

## How to use

<details><summary>A classic way to use purgatory</summary>

If you can specify new algorithms for testing by editing src/main.cc, use print statements or assertions to validate logic quickly before formalizing tests.

</details>

<details><summary>If you are running unit testing with GoogleTest</summary>

purgatory uses GoogleTest for reliable, isolated testing.

```shell
cmake -DCAMKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=c++ -DBUILD_TESTING=ON -B build
cmake --build build -j$(nproc)
cd build
ctest --output-on-failure -j$(nproc)
```
To add new test cases, edit test/test.cc. All tests should assert correctness, edge cases, and maintainability. 

</details>

## Design principles

- Enable rapid development and prototyping of algorithm solutions
- Encourage test-driven development (TDD) with clean separation
- Support embedded and system-level protability

## Contributing

If you're inspired to contribute, whether through new test cases, algorithm enhancements, or tooling improvements, your efforts are truly appreciated.
