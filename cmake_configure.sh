#!/bin/bash

mkdir -p build && cd build
cmake --toolchain cmake/toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ../

