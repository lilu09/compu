
#include <iostream>
#include <string>
#include <Cap.h>
#include <helperFactory.h>

using namespace std;


string Cap::getResult(string value)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	istringstream iss(value);
	ostringstream oss;
	char c;
	while(iss.good())
	{
		iss>>c;
		 if(c<=122 && c>=97)
				   c=c-32;
		 oss<<c;
	}
	return oss.str();
}

