#include <iostream>
#include <string>
#include <TASKSYNC.h>

#include <helperFactory.h>

using namespace std;


string TASKSYNC::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...

	ParamList *paramList;	
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");

	string result="";
	// if it should be synchronous based on parameter list
	if(paramList->requireSynchronous())
	{
		result= "task->synchronous = 1;";
	}
	else
	{
		result= "task->synchronous = 0;";
	}
	
	return result;
}

