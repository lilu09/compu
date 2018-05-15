#!/bin/bash

set -e
set -o pipefail

compose main.xml
make  &>/dev/null
echo 
echo 
echo 
./main 2>/dev/null
echo 
echo 
echo 
STARPU_NCPUS=0 STARPU_NCUDA=1 ./main  2>/dev/null
echo 
echo 
echo 
STARPU_NCPUS=4 STARPU_NCUDA=0 ./main  2>/dev/null
make clean
rm ./makefile ./vector_scale_wrapper.h ./peppher.h
