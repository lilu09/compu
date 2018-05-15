#include <iostream>
#include <string>
#include <ROAA2.h>
#include <error.h>

using namespace std;


string ROAA2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	string result="";	
	
	if(!paramList->cg_paramList->isAsynchronousCall()) // if there are no read only parameters to be added.
		result=paramList->getROAA2(com->intfc->name);

	return result;
}

