#include <iostream>
#include <string>
#include <SOU2.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string SOU2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...

/* 
 * In case of repetitive execution, it would be non-optimal to load and unload opencl kernel for each execution.
 * A better way could be to dont do it all and let starpu_shutdown to release these resources.
 */
  	
	
//	if(com->configure->exist("OPENCL"))
//	{
//	Helper *helper=helperFactory::createHelper("SOPN2");
//	string result=helper->getResult(com);
//	return "starpu_opencl_unload_opencl(&"+result+");";
//	}
//	else
	return " ";

}

