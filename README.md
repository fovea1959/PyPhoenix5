# PyPhoenix5 binding

These are bindings from Python to Cross The Road Electronics phoenix5 library. Much of this is from pybind11 examples.

## How to build this puppy

This is from a fresh Raspberry Pi bookworm install:

```
sudo apt install git gh cmake python3-full python3-dev python3-pip
pip install --user --break-system-packages pybind11-stubgen
git clone --recursive https://github.com/fovea1959/PyPhoenix5.git
cd PyPhoenix5
mkdir build
cd build
cmake -Wno-dev ..
make
cd ..
./makestubs.sh
```
