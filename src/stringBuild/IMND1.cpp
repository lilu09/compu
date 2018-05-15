#include <iostream>
#include <string>
#include <IMND1.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string IMND1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->configure->get("CUDA"))
		return com->configure->get("CUDA")->name;
	else 
		return "No CPU implementation";
}

