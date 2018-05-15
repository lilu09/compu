#include <iostream>
#include <string>
#include <CLMS2.h>
#include <helperFactory.h>
#include <error.h>

using namespace std;


string CLMS2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	ParamList *paramList;
	
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");
	
	Helper *helper=helperFactory::createHelper("SCLBO2");
	string result1="NF";
	if(helper)
	{
		result1 = helper->getResult(com);
		delete helper;
	}
	
	helper=helperFactory::createHelper("CLN2");
	if(helper)
	{
		result1 += "->" + helper->getResult(com);
		delete helper;
	}
		
	string result=paramList->getCLMS2(result1);

	return result;
}

