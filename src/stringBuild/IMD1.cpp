#include <iostream>
#include <string>
#include <IMD1.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;

string IMD1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["IMD1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		string res = capitalizeString(trimSpaces(result->pop()));
		res = ((res == "TRUE" || res == "1")? "1" : "0");
		return res;
	}
	return "";
}

