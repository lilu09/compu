#include <iostream>
#include <string>
#include <DRS2.h>
#include <error.h>

using namespace std;


string DRS2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	
	if(com->intfc->methods->getFirst())
		paramList = com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	string result=paramList->getDRS2();

	return result;
}

