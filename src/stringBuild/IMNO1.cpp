#include <iostream>
#include <string>
#include <IMNO1.h>
#include <ComConfig.h>

using namespace std;


string IMNO1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->configure->get("OPENCL"))
		return com->configure->get("OPENCL")->name;
	else 
		return "No CPU implementation";
}

