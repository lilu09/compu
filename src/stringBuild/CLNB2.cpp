#include <iostream>
#include <string>
#include <CLNB2.h>
#include <helperFactory.h>

using namespace std;

string CLNB2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return "cl_"+com->intfc->name+"_init";
}

