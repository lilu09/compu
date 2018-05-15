#include <iostream>
#include <string>
#include <EF2.h>

#include <helperFactory.h>
#include <methods.h>

using namespace std;

string EF2::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result=com->impl->cmpList->getFirst()->obj;
	removeSuffix(result,'.');
	return result;
}

