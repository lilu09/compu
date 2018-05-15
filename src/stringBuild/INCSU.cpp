#include <iostream>
#include <string>
#include <INCSU.h>

#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;


string INCSU::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result="";
	if(com->configure->get("CUDA")->tpltType=="template")
	{
		result=com->intfc->impPath+com->configure->get("CUDA")->source;
		result='"'+result+'"';
		result="#include "+result;
	}

	return result;
}

