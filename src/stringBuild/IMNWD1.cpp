
#include <iostream>
#include <string>
#include <IMNWD1.h>
#include <helperFactory.h>

using namespace std;

string IMNWD1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("IMND1");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
	return result+"_wrapper";
}

