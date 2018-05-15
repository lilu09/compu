#!/bin/bash

set -e
set -o pipefail


#if [ $# != 2 ] 
#then
	#echo "Wrong number of parameters, should be one!"
	#exit 1
#fi

expr=$1

xpdl_lib_prepare_statement=$2


echo '#include <stdio.h>
#include <xpdl.hpp>

' > engine.cpp

echo $xpdl_lib_prepare_statement >> engine.cpp

echo '

int main(int argc, const char *argv[])
{
	printf("%u", ' >> engine.cpp
echo $expr >> engine.cpp
echo ");
	return 0;
}" >> engine.cpp


#g++ -O3 -I /home/lu/Documents/Research/research_original_data/YearlyData/2016/001.HipeacConference/2.Demo/2.XPDL/2.my/ engine.cpp -std=c++11 -o engine &> /dev/null
g++ -O3 -I /home/lu/Documents/Project/XPDL/xpdl_project/src engine.cpp -std=c++11 -o engine &> /dev/null
echo `./engine`
rm engine engine.cpp
