#include <iostream>
#include <string>
#include <IMNWO1.h>

#include <helperFactory.h>

using namespace std;

string IMNWO1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("IMNO1");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
	return result+"_wrapper";
}

