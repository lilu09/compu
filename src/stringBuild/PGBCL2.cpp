#include <iostream>
#include <string>
#include <PGBCL2.h>

#include <helperFactory.h>
#include <EnvVar.h>

using namespace std;

extern EnvVar env;

string PGBCL2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
    Helper *helper=helperFactory::createHelper("ROCNR2");
	string temp="NF";
	
	if(helper)
	{
		temp = helper->getResult(com);
		delete helper;
	}
	
	if(com->intfc)
	{
		string str=com->intfc->getRawTemplateTypesStr();
		if(!str.empty())
			temp += "<" + str + ">";
	}
	env.message = temp;
	
	ParamList *paramList;
	
	if(com->intfc->methods->getFirst())
		paramList= com->intfc->methods->getFirst()->params;
	else
		error("No method definition in Interface XML file!!!");

	//return "yes";
	return paramList->getPGB2(true);
}

