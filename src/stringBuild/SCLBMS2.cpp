#include <iostream>
#include <string>
#include <SCLBMS2.h>
#include <helperFactory.h>

using namespace std;

string SCLBMS2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("SCLBO2");
	string result1="NF", clStName = "NF";
	if(helper)
	{
		clStName = helper->getResult(com);
		delete helper;
	}
		
	helper=helperFactory::createHelper("CLN2");
	if(helper)
	{
		result1 = clStName + "->" + helper->getResult(com);
		delete helper;
	}
	
	string result = "memset( &(" + result1 + "), 0, sizeof(" + result1 + "));";
	
	if(com->intfc->useHistoryModels)
	{
		string name= clStName + "->pm_history_" + com->intfc->name;
		result += "\n memset( &(" + name + "), 0, sizeof(" + name + "));";
	}
	else if(com->intfc->useRegressionModels)
	{
		string name= clStName + "->pm_regression_" + com->intfc->name;
		result += "\n memset( &(" + name + "), 0, sizeof(" + name + "));";
	}
	else if(com->intfc->useNLRegressionModels)
	{
		string name= clStName + "->pm_nl_regression_" + com->intfc->name;
		result += "\n memset( &(" + name + "), 0, sizeof(" + name + "));";
	}
			
	return result;
}

