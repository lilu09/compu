#include <iostream>
#include <string>
#include <TPLT.h>
#include <InfContainer.h>
#include <EnvVar.h>
#include <methods.h>

using namespace std;

extern EnvVar env;

string TPLT::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["TPLT"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		return trimSpaces(result->pop());
	}
	return "";
}

