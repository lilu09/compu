#include <iostream>
#include <string>
#include <DOPENCL1.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;

string DOPENCL1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["DOPENCL1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		string res = capitalizeString(trimSpaces(result->pop()));
		res = ((res == "TRUE" || res == "1")? "1" : "0");
		return res;
	}
	return "";
}

