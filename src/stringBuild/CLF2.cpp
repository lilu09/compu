#include <iostream>
#include <string>
#include <CLF2.h>
#include <helperFactory.h>

using namespace std;

string CLF2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("CCQN2");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
	return "clFinish("+result+");";
}

