#include <iostream>
#include <string>
#include <EXTSU.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string EXTSU::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result="";
	if(com->configure->get("CUDA")->tpltType!="template")
	{
		Helper *helper=helperFactory::createHelper("IMND1");
		string result1="NF";
		if(helper)
		{
			result1 = helper->getResult(com);
			delete helper;
		}
		helper=helperFactory::createHelper("IPL1");
		string result2="NF";
		if(helper)
		{
			result2 = helper->getResult(com);
			delete helper;
		}
		result="extern void "+result1+"("+result2+");";
	}

	return result;
}


