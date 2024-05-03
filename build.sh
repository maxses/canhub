#!/bin/bash


set -e -u

O=build

rm -rf $O
mkdir -p $O
cd $O

cmake .. '-GCodeBlocks - Unix Makefiles'

make -j96

echo "[$0] fin."

#---fin------------------------------------------------------------------------
