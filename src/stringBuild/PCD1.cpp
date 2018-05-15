#include <iostream>
#include <string>
#include <PCD1.h>

#include <helperFactory.h>

using namespace std;


string PCD1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...

	ParamList *paramList;	
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");

	return paramList->getPCD1();
}

