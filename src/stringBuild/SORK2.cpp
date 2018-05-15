#include <iostream>
#include <string>
#include <SORK2.h>
#include <helperFactory.h>

using namespace std;

string SORK2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("CKN2");
	string result="NF";
	if(helper)
	{
		result=helper->getResult(com);
		delete helper;
	}
	return "starpu_opencl_release_kernel("+result+");";
}

