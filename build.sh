#!/bin/bash

# End the script immediately if any command or pipe exits with a non-zero status.
set -euo pipefail

# create a build folder for the out-of-source build
mkdir -p build

# switch to build directory
cd build

# Configure
cmake -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug ..

# Build (for Make on Unix equivalent to `make -j $(nproc)`)
cmake --build . --config Debug -- -j $(nproc)

# Test
ctest -j $(nproc) --output-on-failure
