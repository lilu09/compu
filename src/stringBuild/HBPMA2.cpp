#include <iostream>
#include <string>
#include <HBPMA2.h>
#include <helperFactory.h>

using namespace std;


string HBPMA2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->intfc->useHistoryModels || com->intfc->useRegressionModels || com->intfc->useNLRegressionModels)
	{
		Helper *helper=helperFactory::createHelper("SCLBO2");
		string structName="NF";
		if(helper)
		{
			structName = helper->getResult(com);
			delete helper;
		}
		string name, result;
		
		if(com->intfc->useHistoryModels)
		{
			name= "pm_history_" + com->intfc->name;
			result = structName + "->" + name + ".type = STARPU_HISTORY_BASED;\n";
		}
		else if(com->intfc->useRegressionModels)
		{
			name= "pm_regression_" + com->intfc->name;
			result = structName + "->" + name + ".type = STARPU_REGRESSION_BASED;\n";
		}
		else	
		{
			name= "pm_nl_regression_" + com->intfc->name;
			result = structName + "->" + name + ".type = STARPU_NL_REGRESSION_BASED;\n";
		}
			
		result = structName + "->" + name + ".symbol = \"" + name + "\";\n" + result;
		
		helper=helperFactory::createHelper("SCLBO2");
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
			result += result1 + ".model = &(" + structName + "->" + name + ");";
			delete helper;
		}
		
		return result;
	}
	return "";
}