#include <iostream>
#include <string>
#include <ROCN2.h>
#include <Interface.h>

using namespace std;


/*
string ROCN2::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{

	meta=env.kb["ROCN2"];
	CALLHELP2
}

string ROCN2::getResult(ImpConfig *conf,map <string, string> *pool)
{


	return "Default";
}
*/
string ROCN2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return "readOnlyArgs_"+com->intfc->name;
}

