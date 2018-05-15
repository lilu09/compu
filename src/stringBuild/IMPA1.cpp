#include <iostream>
#include <string>
#include <IMPA1.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;



string IMPA1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["IMPA1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		//cout<<"##exe"<<endl;
		return trimSpaces(result->pop());
	}
	warn("Cannot find path for component implementations, IMPA1::getResult(Node *tree) method");
	return "";
}

