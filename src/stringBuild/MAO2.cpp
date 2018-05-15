#include <iostream>
#include <string>
#include <MAO2.h>
#include <CompileStmtList.h>

using namespace std;


string MAO2::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return com->getOutputName();
}

