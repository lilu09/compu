#include <iostream>
#include <string>
#include <SCLBO2.h>
#include <helperFactory.h>

using namespace std;

string SCLBO2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return "objSt_" + com->intfc->name;
}

