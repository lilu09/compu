#include <iostream>
#include <string>
#include <ROATSA2.h>

#include <helperFactory.h>


using namespace std;

/*
string ROCNR2::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{
	Helper *helper=helperFactory::createHelper("IN1");
	meta=env.kb["IN1"];
	string result=helper->getResult(meta,conf,pool);
	return "ROA_"+result;
}

string ROCNR2::getResult(ImpConfig *conf,map <string, string> *pool)
{


	return "Default";
}
*/
string ROATSA2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
		
	if(paramList->cg_paramList->paramReadOnly->empty()) // if there are no read only parameters to be added.
		return "";
	
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
	
	return "task->cl_arg_size = sizeof(" + result + ");";
}

