#include <iostream>
#include <string>
#include <IN1.h>
#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;

string IN1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult(Node)") // used for debugging purposes to trace problems...
	
	string meta=env.kb["IN1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		//cout<<"##exe"<<endl;
		return trimSpaces(result->pop());
	}
	warn("The interface name could not be found, IN1::getResult(Node *tree) method");
	return "";
}

string IN1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return com->intfc->name;
}

