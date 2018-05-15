#include <iostream>
#include <string>
#include <SCLSCD2.h>

#include <InfContainer.h>
#include <methods.h>
#include <helperFactory.h>

using namespace std;

string SCLSCD2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result = "";
	
	Helper *helper=helperFactory::createHelper("TMTPST2");
	if(helper)
    {
        result = trimSpaces(helper->getResult(com));
        delete helper;  
    }
    
    string CLN2 = "NF";
    helper=helperFactory::createHelper("CLN2");
	if(helper)
    {
        CLN2 = trimSpaces(helper->getResult(com));
        delete helper;  
    }
	 
	string HBPM2 = "NF";  
	helper=helperFactory::createHelper("HBPM2");
	if(helper)
    {
        HBPM2 = trimSpaces(helper->getResult(com));
        delete helper;  
    }
    
    
    string CLNB2 = "NF";  
	helper=helperFactory::createHelper("CLNB2");
	if(helper)
    {
        CLNB2 = trimSpaces(helper->getResult(com));
        delete helper;  
    }
    
    
    string SCLB2 = "NF";  
	helper=helperFactory::createHelper("SCLB2");
	if(helper)
    {
        SCLB2 = trimSpaces(helper->getResult(com));
        delete helper;  
    }
      
    if(result.empty()) // generate C-compatible code using typedef....
		result += "typedef struct \n{\n\tstruct starpu_codelet " + CLN2  + ";\n\t" + HBPM2 + "\n\t int " + CLNB2+";\n} "+ SCLB2 + ";";
	else
		result += "struct "+SCLB2+"\n{\n\tstruct starpu_codelet " + CLN2  + ";\n\t" + HBPM2 + "\n\t int " + CLNB2+";\n};";
	
	return result;
}

