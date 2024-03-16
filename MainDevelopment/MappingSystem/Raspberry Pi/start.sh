#!/bin/bash

## Kill background processe(s) on exit (rn only keyboard_listener.py)
# From https://stackoverflow.com/a/22644006
trap "exit" INT TERM
trap "kill 0" EXIT

python3 keyboard_listener.py &
python3 simplesocket_v2.py
