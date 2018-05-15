#include <iostream>
#include <string>
#include <HBPM2.h>


using namespace std;


string HBPM2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	if(com->intfc->useHistoryModels)
		return "struct starpu_perfmodel pm_history_"+com->intfc->name+";";
	else if(com->intfc->useRegressionModels)
		return "struct starpu_perfmodel pm_regression_"+com->intfc->name+";";
	else if(com->intfc->useNLRegressionModels)
		return "struct starpu_perfmodel pm_nl_regression_"+com->intfc->name+";";	
	return "";
}

