#!/usr/bin/env bash
export PYTHONPATH=$PYTHONPATH:$HOME/lib/python
python3 -c 'import simdjson; simdjson.is_valid("jsonexamples/twitter.json");' 