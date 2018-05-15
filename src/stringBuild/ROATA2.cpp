#include <iostream>
#include <string>
#include <ROATA2.h>

#include <helperFactory.h>


using namespace std;

string ROATA2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	if(paramList->cg_paramList->paramReadOnly->empty()) // if there are no read only parameters to be added.
		return "";
	
	string result = "";
	if(paramList->cg_paramList->isAsynchronousCall()) // if there are no read only parameters to be added.
	{		
		result +=  "task->callback_func = free;\n";
		result += "task->callback_arg = (void *) arg_"+ com->intfc->name +";\n";
		result += "task->cl_arg = arg_"+ com->intfc->name + ";";
	}
	else
		result += "task->cl_arg = &arg_"+ com->intfc->name + ";";
	
	return result;
}

