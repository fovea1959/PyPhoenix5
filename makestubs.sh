#!/bin/bash

. venv/bin/activate
PYTHON_PATH=bin LD_LIBRARY_PATH=bin pybind11-stubgen PyPhoenix5
find stubs -ls
