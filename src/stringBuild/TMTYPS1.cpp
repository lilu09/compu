#include <iostream>
#include <string>
#include <TMTYPS1.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;

string TMTYPS1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["TMTYPS1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		return trimSpaces(result->pop());
	}
	return "";
}

