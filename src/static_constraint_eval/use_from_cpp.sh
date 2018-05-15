#!/bin/bash

set -e
set -o pipefail

#g++ ./use_from_cpp.cpp -std=c++11 -g
#cgdb ./a.out
g++ ./use_from_cpp.cpp -std=c++11
./a.out
rm a.out
