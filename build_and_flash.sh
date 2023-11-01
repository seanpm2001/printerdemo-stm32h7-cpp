#!/bin/bash

set -o nounset 
set -o errexit

cmake -S . -B Debug -DCMAKE_TOOLCHAIN_FILE=${PWD}/cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Debug -GNinja

# Check the exit status of the last command
if [ $? -eq 0 ]; then
    echo "CMake config was successful."
else
    echo "CMake config failed."
    exit 1
fi

cmake --build Debug

# Check the exit status of the last command
if [ $? -eq 0 ]; then
    echo "CMake build was successful."
    openocd -f interface/stlink.cfg -f target/stm32h7x.cfg -c "program ./Debug/StmTextCMake.elf reset exit"
else
    echo "CMake build failed."
fi
