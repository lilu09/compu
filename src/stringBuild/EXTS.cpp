#include <iostream>
#include <string>
#include <EXTS.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;


string EXTS::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result="";
	if(com->configure->get("CPU")->tpltType!="template")
	{
		Helper *helper=helperFactory::createHelper("IMNP1");
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


