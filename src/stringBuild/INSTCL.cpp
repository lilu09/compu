#include <iostream>
#include <string>
#include <INSTCL.h>
#include <ComConfig.h>

#include <helperFactory.h>
#include <methods.h>

using namespace std;

string INSTCL::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	vector<DepComp *>::iterator it;
	for(it=com->impl->depCompList->getBegin();it!=com->impl->depCompList->getEnd();it++)
	{
		if( (*it)->com->configure->get("OPENCL") )
			return "#include <starpu_opencl.h>";
	}

	return "";
}

