#include <iostream>
#include <string>
#include <SRL2.h>
#include <ComConfig.h>

using namespace std;

string SRL2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result1="",result2="",result3="",result="";
	if(com->configure->get("CPU"))
	    result1="|STARPU_CPU";
	if(com->configure->get("CUDA"))
		result2="|STARPU_CUDA";
	if(com->configure->get("OPENCL"))
		result3="|STARPU_OPENCL";
	result="0"+result1+result2+result3;
	return result;
}

