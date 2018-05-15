#include <iostream>
#include <string>
#include <INWH2.h>

#include <helperFactory.h>

#include <Interface.h>
#include <EnvVar.h>

extern EnvVar env;


using namespace std;

/*
string INWH2::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{
	 //TRYPOOL("INWH2")
	meta=env.kb["INWH2"];
	CALLHELP2

	return "";
}

string INWH2::getResult(ImpConfig *conf, map <string, string> *pool)
{
	return "Default";
}
*/
string INWH2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return com->intfc->name+"_wrapper" + env.wrapperFilesExt;
}

