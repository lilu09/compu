#include <iostream>
#include <ImplType.h>
#include <error.h>
#include <methods.h>

using namespace std;

ImplType::ImplType():type("NULL")
{
	
};

void ImplType::setType(string value)
{
	// trim spaces and captialize
	value = trimSpaces(value);
	value = capitalizeString(value);
	
	if(value=="CPU"|| value=="OPENMP" || value=="CUDA"||value=="OPENCL")
		type=value;
	else
		error("Implementation type is unkown: " + value + "!");
};

string ImplType::getType()
{
	return type;
};





