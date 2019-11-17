#!/bin/bash
set -e
sudo apt update
sudo apt install -y build-essential uuid-dev iasl git nasm gcc-aarch64-linux-gnu bc
curdir="$PWD"
cd "$curdir"
.Sdm835/firstrun.sh
.Sdm835/build.sh
