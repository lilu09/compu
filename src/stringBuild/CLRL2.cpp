#include <iostream>
#include <string>
#include <CLRL2.h>
#include <helperFactory.h>


using namespace std;


string CLRL2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
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
	
	helper=helperFactory::createHelper("SRL2");
	string result2="NF";
	if(helper)
	{
		result2 = helper->getResult(com);
		delete helper;
	}
	return result1+".where ="+result2+";";
}
