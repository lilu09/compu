#include <iostream>
#include <string>
#include <CLN2.h>


using namespace std;

/*
string CLN2::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{
	TRYPOOL2("CLN2")
	Helper *helper=helperFactory::createHelper("IN1");
	string result=helper->getResult("",conf,pool);
	return "cl_"+result;
}

string CLN2::getResult(ImpConfig *conf,map <string, string> *pool)
{
	Helper *helper=helperFactory::createHelper("IN1");
	string result=helper->getResult(conf,pool);
	return "cl_"+result;
}
*/
string CLN2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return "cl_"+com->intfc->name;
}

