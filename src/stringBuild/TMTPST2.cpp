#include <iostream>
#include <string>
#include <TMTPST2.h>

#include <InfContainer.h>
#include <methods.h>

using namespace std;

string TMTPST2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	if(com->intfc)
	{
		if(com->intfc->templateTypesVec.empty())
			return "";
			
		string result = "template <";
		
		result += "typename "+com->intfc->templateTypesVec[0];
		
		for(int i=1; i<com->intfc->templateTypesVec.size(); i++)
		{
			result +=", typename "+com->intfc->templateTypesVec[i];
		}
		result += ">\n";
		
		return result;
	}
	return "";
}

