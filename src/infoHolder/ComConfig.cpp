#include <ComConfig.h>
#include <methods.h>

using namespace std;

ComConfig::ComConfig()
{
	config["CPU"]=0;
	config["CUDA"]=0;
	config["OPENCL"]=0;
}

void ComConfig::set(string type,Implementation *imp)
{ 
	if(capitalizeString(trimSpaces(type)) == "OPENMP")
		config["CPU"]=imp;
	else	
		config[capitalizeString(trimSpaces(type))]=imp;
}

Implementation *ComConfig::get(string type)
{
	if(config.count(capitalizeString(trimSpaces(type)))>0)
		return config[capitalizeString(trimSpaces(type))];
	else 
	{
		warn("No implementation is specified for type: "+ capitalizeString(trimSpaces(type)) + ", returning NULL");
		return 0;
	}
}

bool ComConfig::exist(string type)
{
	return config[capitalizeString(trimSpaces(type))]!=0;
}

void ComConfig::printMe()
{
	cout<<"Configure: "<<endl;
	cout<<"CPU: "<<(get("CPU")==0?"Null":get("CPU")->name)<<endl;
	cout<<"CUDA: "<<(get("CUDA")==0?"Null":get("CUDA")->name)<<endl;
	cout<<"OPENCL: "<<(get("OPENCL")==0?"Null":get("OPENCL")->name)<<endl;
}

