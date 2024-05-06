#!/bin/bash

PYTHONPATH=bin LD_LIBRARY_PATH=bin ~/.local/bin/pybind11-stubgen PyPhoenix5
find stubs -ls
