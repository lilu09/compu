#include <iostream>
#include <string>
#include <INCS.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string INCS::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result="";
	if(com->configure->get("CPU")->tpltType=="template")
	{
		result=com->intfc->impPath+com->configure->get("CPU")->source;
		result='"'+result+'"';
		result="#include "+result;
	}

	return result;
}

