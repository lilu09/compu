#include <iostream>
#include <string>
#include <RIN1.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>

using namespace std;



string RIN1::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
    InfContainer *inf=fetchTreeIterTwo(env.kb["RIN1"],tree);
	if(inf)
		return inf->converge(" ");
	else 
		return "";
}

