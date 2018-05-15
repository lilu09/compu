#include <iostream>
#include <string>
#include <SOLK2.h>
#include <helperFactory.h>


using namespace std;


string SOLK2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("CKN2");
	string result1="NF";
	if(helper)
	{
		result1=helper->getResult(com);
		delete helper;
	}

	helper=helperFactory::createHelper("CCQN2");
	string result2="NF";
	if(helper)
	{
		result2=helper->getResult(com);
		delete helper;
	}

	helper=helperFactory::createHelper("SOPN2");
	string result3="NF";
	if(helper)
	{
		result3=helper->getResult(com);
		delete helper;
	}

	helper=helperFactory::createHelper("LKS2");
	string result4="NF";
	if(helper)
	{
		result4=helper->getResult(com);
		delete helper;
	}

    result4='"'+result4+'"';
	string result="int err = starpu_opencl_load_kernel(&"+result1+", &"+result2+", "+result3+", "+result4+", devid);";
	
    return result;
}

