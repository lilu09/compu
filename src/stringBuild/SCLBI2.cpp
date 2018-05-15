#include <iostream>
#include <string>
#include <SCLBI2.h>
#include <helperFactory.h>

using namespace std;

string SCLBI2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("SCLBO2");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
		
	helper=helperFactory::createHelper("CLNB2");
	if(helper)
	{
		result += "->" + helper->getResult(com) + " = 0;";
		delete helper;
	}
		
	return result;
}

