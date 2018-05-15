#include <iostream>
#include <string>
#include <SN1.h>
#include <InfContainer.h>
#include <EnvVar.h>
#include <methods.h>


using namespace std;

extern EnvVar env;

string SN1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	InfContainer *result=fetchTree(env.kb["SN1"],tree);
	if(result && !result->isEmpty() )
	{
		//cout<<"##exe"<<endl;
		return trimSpaces(result->pop());
	}

	return "Helper not found";

}


