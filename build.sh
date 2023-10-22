#!/bin/bash

set -o nounset 
set -o errexit

cmake -S . -B Debug -DCMAKE_TOOLCHAIN_FILE=${PWD}/cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Debug -GNinja
cmake --build Debug
