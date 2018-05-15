#include <iostream>
#include <string>
#include <OPCC2.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string OPCC2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->configure->exist("OPENCL"))
	{
		Helper *helper=helperFactory::createHelper("SCLBO2");
		string result1="NF";
		if(helper)
		{
			result1 = helper->getResult(com);
			delete helper;
		}
		
		helper=helperFactory::createHelper("CLN2");
		if(helper)
		{
			result1 += "->" + helper->getResult(com);
			delete helper;
		}
		
		helper=helperFactory::createHelper("IMNWO1");
		string result2="NF";
		if(helper)
		{
			result2 = helper->getResult(com);
			delete helper;
		}
		
		if(com->intfc)
		{
			string str=com->intfc->getRawTemplateTypesStr();
			if(!str.empty())
				result2 += "<" + str + ">";
		}
		
		return result1+".opencl_funcs[0]="+result2+";\n"+result1+".opencl_funcs[1]=NULL;\n";
	}
	else
		return " ";
}

