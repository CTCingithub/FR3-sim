#!/bin/bash

# clear
echo "Building and running..."

if [ -d "build" ]; then
    echo "Found existing build directory..."
    rm -rf build/
else
    echo "No existing build directory found, creating one..."
fi
mkdir build

rm -rf bin/
cd build/
echo "Building in $(pwd)"
cmake .. -DMUJOCO_HOME=/usr/local/MUJOCO/mujoco-3.3.0
make -j4

cd ..