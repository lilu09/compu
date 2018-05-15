#include <iostream>
#include <string>
#include <TWFA.h>
#include <helperFactory.h>


using namespace std;



string TWFA::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result = "";

	ParamList *paramList;
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	if(paramList->requireTaskWait()) 
		return "starpu_task_wait_for_all();\n";
		
	return result;
}

