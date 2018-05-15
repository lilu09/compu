#include <iostream>
#include <string>
#include <IMNP1.h>
#include <InfContainer.h>
#include <methods.h>
#include <helperFactory.h>
#include <EnvVar.h>
#include <ComConfig.h>


using namespace std;

extern EnvVar env;

string IMNP1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult(Node)") // used for debugging purposes to trace problems...
	
	InfContainer *result=fetchTree(env.kb["IMNP1"],tree);
	if(result && !result->isEmpty() )
	{
		return trimSpaces(result->pop());
	}
	warn("Problem while generating implementation name in IMNP1::getResult(Node *tree) method");
	return "Helper not found";
}

string IMNP1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->configure->get("CPU"))
		return com->configure->get("CPU")->name;
	else 
		return "No CPU implementation";
}

