#include <iostream>
#include <string>
#include <ROSCD2.h>

#include <InfContainer.h>
#include <methods.h>
#include <helperFactory.h>

using namespace std;

string ROSCD2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result = "";
	
	Helper *helper=helperFactory::createHelper("TMTPST2");
	if(helper)
    {
        result = trimSpaces(helper->getResult(com));
        delete helper;  
    }
    
    string ROPD1 = "NF";
    helper=helperFactory::createHelper("ROPD1");
	if(helper)
    {
        ROPD1 = trimSpaces(helper->getResult(com));
        delete helper;  
    }
	 
	string ROCNR2 = "NF";  
	helper=helperFactory::createHelper("ROCNR2");
	if(helper)
    {
        ROCNR2 = trimSpaces(helper->getResult(com));
        delete helper;  
    }  
    if(result.empty()) // generate C-compatible code using typedef....
		result += "typedef struct \n{\n\t" + ROPD1 + "\n} "+ ROCNR2 + ";";
	else
		result += "struct " + ROCNR2+ "\n{\n\t" + ROPD1 + "\n};";
	
	
	return result;
}

