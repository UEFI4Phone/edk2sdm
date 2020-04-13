#!/bin/bash
set -e
sudo apt update
sudo apt install -y build-essential uuid-dev iasl git nasm gcc-aarch64-linux-gnu bc
curdir="$PWD"
cd "$curdir"
export PACKAGES_PATH=$PWD/edk2:$PWD/edk2-platforms:$PWD/Sdm835
export WORKSPACE=$PWD/workspace
./build.sh
