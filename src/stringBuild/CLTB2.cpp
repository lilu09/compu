#include <iostream>
#include <string>
#include <CLTB2.h>

#include <helperFactory.h>

using namespace std;


string CLTB2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("SCLBO2");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
	
	helper=helperFactory::createHelper("CLN2");
	if(helper)
	{
		result += "->" + helper->getResult(com);
		delete helper;
	}
	
	return "task->cl = &("+result+");";
}

