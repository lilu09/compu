#include <iostream>
#include <string>
#include <LCLSC2.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string LCLSC2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->configure->exist("OPENCL"))
	{
		Helper *helper=helperFactory::createHelper("LCLS2");
		string result1="NF";
		if(helper)
		{
			result1 = helper->getResult(com);
			delete helper;
		}
		
		helper=helperFactory::createHelper("IN1");
		string result3="NF";
		if(helper)
		{
			result3 = helper->getResult(com);
			delete helper;
		}
		
		helper=helperFactory::createHelper("SOPN2");
		string result2="NF";
		if(helper)
		{
			result2 = helper->getResult(com);
			delete helper;
		}
		
		result1='"'+result3+"/"+result1+'"';
		string result="if (!" + result2 + ") {\n";
		result += result2 +" = (struct starpu_opencl_program *)malloc ( sizeof(struct starpu_opencl_program));\n";
		result += "int i = starpu_opencl_load_opencl_from_file("+result1+" ,"+result2+", NULL);\n }";
	
		return result;
	}
	else
		return " ";
}

