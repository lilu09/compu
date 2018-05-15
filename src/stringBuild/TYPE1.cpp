#include <iostream>
#include <string>
#include <TYPE1.h>
#include <InfContainer.h>
#include <EnvVar.h>
#include <methods.h>

using namespace std;

extern EnvVar env;

string TYPE1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["TYPE1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		return trimSpaces(result->pop());
	}
	warn("The implementation type is either null or incorrect (Should be either CUDA, CPU or OPENCL), TYPE1::getResult() method");
	return "";
}


