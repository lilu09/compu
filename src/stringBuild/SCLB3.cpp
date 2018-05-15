#include <iostream>
#include <string>
#include <SCLB3.h>
#include <helperFactory.h>

using namespace std;

string SCLB3::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("SCLB2");
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
		
	return result;
}

