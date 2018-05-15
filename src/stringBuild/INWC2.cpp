#include <iostream>
#include <string>
#include <INWC2.h>
#include <helperFactory.h>

using namespace std;

/*
string INWC2::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{
	meta=env.kb["INWC2"];
	CALLHELP2
}

string INWC2::getResult(ImpConfig *conf, map <string, string> *pool)
{
	string meta=env.kb["INWC2"];
	CALLHELP2
}
*/
string INWC2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string tmp=com->intfc->name+"_wrapper";
	Helper *helper=helperFactory::createHelper("Cap");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(tmp);
		delete helper;
	}
	return result;
}

