#include <iostream>
#include <string>
#include <IMNWP1.h>

#include <helperFactory.h>

using namespace std;




/*
string IMNWP1::getResult(Node *tree)
{
	Helper *helper=helperFactory::createHelper("IMNP1");
	string result=helper->getResult(tree);
	return result+"_wrapper";
}
*/

string IMNWP1::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("IMNP1");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(com);
		delete helper;
	}
	return result+"_wrapper";
}

