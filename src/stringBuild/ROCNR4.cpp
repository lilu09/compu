#include <iostream>
#include <string>
#include <ROCNR4.h>

#include <helperFactory.h>


using namespace std;


string ROCNR4::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	if(paramList->cg_paramList->paramReadOnly->empty()) // if there are no read only parameters to be added.
		return "";
	
	if(paramList->cg_paramList->isAsynchronousCall()) // if there are no read only parameters to be added.
	{		
		Helper *helper=helperFactory::createHelper("ROCNR2");
		string result="NF";
		if(helper)
		{
			result = helper->getResult(com);	
			delete helper;
		}
		
		if(com->intfc)
		{
			string str=com->intfc->getRawTemplateTypesStr();
			if(!str.empty())
				result += "<" + str + ">";
		}
		return result + " *arg_"+com->intfc->name+" = (" + result + " *)malloc (sizeof (" + result + "));";
	}
	else
		return "";	
}

