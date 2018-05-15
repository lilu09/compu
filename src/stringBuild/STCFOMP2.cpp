#include <iostream>
#include <string>
#include <STCFOMP2.h>
#include <ComConfig.h>

#include <helperFactory.h>
#include <methods.h>

using namespace std;

string STCFOMP2::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->hasOpenMPImpl())
		return "conf.single_combined_worker = 1; \\\n conf.sched_policy_name = \"pheft\"; ";
	return "";
}

