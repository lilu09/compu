#include <iostream>
#include <string>
#include <SCLB2.h>
#include <helperFactory.h>

using namespace std;

string SCLB2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return "struct_" + com->intfc->name;
}

