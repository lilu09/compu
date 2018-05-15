#include <iostream>
#include <string>
#include <PIFN1.h>
#include <InfContainer.h>
#include <EnvVar.h>
#include <methods.h>


using namespace std;

extern EnvVar env;
/*
string PIFN1::getResult(string meta, ImpConfig *conf,map <string, string> *pool)
{
	Helper *helper=helperFactory::createHelper("IN1");
	string result=helper->getResult("add $IMNP1 _wrapper",conf,pool);
	return "cl.cpu_func="+result+";";
}
*/

string PIFN1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string meta=env.kb["PIFN1"];
	InfContainer *result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		//cout<<"##exe"<<endl;
		return trimSpaces(result->pop());
	}

	return "not found";
}

