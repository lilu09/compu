#include <iostream>
#include <string>
#include <INWQM2.h>
#include <DepCompList.h>

#include <helperFactory.h>
#include <methods.h>
#include <EnvVar.h>

extern EnvVar env;

using namespace std;

string INWQM2::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result="", curr="";
	vector<DepComp *>::iterator it;
	for(it=com->impl->depCompList->getBegin();it!=com->impl->depCompList->getEnd();it++)
	{
		curr=(*it)->infName;
		curr='"'+curr+"_wrapper"+ env.wrapperFilesExt+'"';
		curr="#include "+curr+" @ ";
		result += curr;
	}

	return result;
}

