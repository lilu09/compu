#include <iostream>
#include <string>
#include <OMPFJM2.h>
#include <helperFactory.h>
#include <ComConfig.h>

using namespace std;

string OMPFJM2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result1="";
	if(com->hasOpenMPImpl()) //com->configure->exist("CPU") && com->configure->get("CPU")->type.getType() == "OPENMP") // An OpenMP mplementation is there and is default for code generation
	{
		Helper *helper=helperFactory::createHelper("SCLBO2");
		
		if(helper)
		{
			result1 = helper->getResult(com);
			delete helper;
		}
		helper=helperFactory::createHelper("CLN2");
		if(helper)
		{
			result1 += "->" + helper->getResult(com);
			result1 = result1 + ".type = STARPU_FORKJOIN;\n" + result1 + ".max_parallelism = INT_MAX;\n";
			delete helper;
		}
	}
	return result1;
}

