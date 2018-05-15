#include <iostream>
#include <string>
#include <ROCNR2.h>

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
string ROCNR2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
//	ParamList *paramList;
//	if(com->intfc->methods->getFirst())
//		paramList= com->intfc->methods->getFirst()->params;
//	else
//		error("No method definition in Interface XML file!!!");
//		
//	if(paramList->cg_paramList->paramReadOnly->empty()) // if there are no read only parameters to be added.
//		return "";
		
	return "ROA_"+com->intfc->name; //+" arg;";
}

