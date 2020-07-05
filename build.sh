#!/usr/bin/env bash
set -o verbose
export PYTHONPATH=$PYTHONPATH:$HOME/lib/python
ARCHFLAGS="" python3 setup.py build 
python3 setup.py install --home=$HOME
