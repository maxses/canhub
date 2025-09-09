#!/bin/bash

set -e
set -u

sudo ip link set down can0
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0

echo "[$0] fin."

#---fin------------------------------------------------------------------------
