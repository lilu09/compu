#include <fstream>
#include <algorithm>
#include <Component.h>
#include <ComConfig.h>
#include <methods.h>
#include <Helper.h>
#include <helperFactory.h>
#include <EnvVar.h>

using namespace std;

extern EnvVar env;

Component::Component(){}

/**  Constructor, initialize memeber variable by syntax tree. If deVar is set to TRUE, then first added implementation of same kind is set as default implementation. This method is useful for building Intermediate Representation. */
Component::Component(Node *tree, bool deVar)
{
	DEBUG_METHOD_ENTRY("Component(Node *, bool)") // used for debugging purposes to trace problems...	
	
	defaultFlag=deVar;
	//create interface
	intfc=new Interface(tree);
	configure=new ComConfig();
	//create implementations
	string fn;
	vector<XmlFile *>::iterator it;
	Node *aTree;
	Implementation *imp;
	for( it=intfc->xmlFiles->getBegin(); it!=intfc->xmlFiles->getEnd();it++)
	{
		buildComponentTree( (*it)->filename , aTree);
		
		Helper *helper=helperFactory::createHelper("IMD1");
		if(helper)
		{
			string ret = helper->getResult(aTree);
			if(ret == "1")
			{
				delete helper;
				continue;
			}
			delete helper;
		}
		
		helper=helperFactory::createHelper("IMNP1");
		string name="NF";
		if(helper)
		{
			name = unCapitalizeString(helper->getResult(aTree));
			delete helper;
		}
		
		if(std::find(env.disableImplList.begin(), env.disableImplList.end(), name)!=env.disableImplList.end())
			continue;
		
		imp=new Implementation(aTree,intfc->impPath);
		//get Type
		impls.insert(pair<string, Implementation *>(imp->type.getType(),imp) );
		//if default, update the configure structures
		
		if(defaultFlag)
		{
			//test if null, then update
			if( !configure->exist( imp->type.getType() ) )
				configure->set(imp->type.getType(),imp);
		}
	}
	
}

void Component::printName(string space)
{
	string sign="+";
	//print interface
	cout<<space<<sign<<"Component: "<<intfc->name<<endl;
	//print implementation
	space="  "+space;
	printImps(space);
}

bool Component::hasOpenMPImpl()
{
	// return true if an OpenMP implementation is selected for code generation.
	return (configure->exist("CPU") && configure->get("CPU")->type.getType() == "OPENMP");
//	multimap<string, Implementation *>::iterator it;
//	for(it=impls.begin();it!=impls.end();it++)
//	{
//		if(it->second->type.getType() == "OPENMP")
//			return true;
//	}
//	return false;
}


void Component::printImps(string space)
{
	multimap<string, Implementation *>::iterator it;
	for(it=impls.begin();it!=impls.end();it++)
	{
		cout<<space<<"-"<<it->second->name<<"  type: "<<it->second->type.getType()<<endl;
	}
}

void Component::printMe()
{
	cout<<"/************************************************/"<<endl;
	cout<<endl<<"Component: "<<intfc->name<<endl<<endl;
	//print configure
	if(configure)
		configure->printMe();
	else
		cout<<"No configure available."<<endl<<endl;
	//print interface
	intfc->printMe();
	//print implementation
	multimap<string, Implementation *>::iterator it;
	for(it=impls.begin();it!=impls.end();++it)
	{
		it->second->printMe();
	}
	cout<<"/************************************************/"<<endl<<endl;
}

void Component::generateWrapper()
{
	DEBUG_METHOD_ENTRY("generateWrapper") // used for debugging purposes to trace problems...	
	
	map <string, string> *pool=new map <string, string>;
	map <string, string> *currPool=new map <string, string>;
	//calculate
	loadVarToMap(env.wrapperHeaderTemplate,currPool);
	(*currPool)["INWH2"]="null";
	updateVariable(currPool,pool,this);

	loadVarToMap(env.wrapperInfTemplate,currPool);
	updateVariable(currPool,pool,this);

    if(configure->exist("CPU"))
	{
		loadVarToMap(env.wrapperCpuTemplate,currPool);
		updateVariable(currPool,pool,this);
	}
	if(configure->exist("CUDA"))
	{
		loadVarToMap(env.wrapperCudaTemplate,currPool);
		updateVariable(currPool,pool,this);
	}
	if(configure->exist("OPENCL"))
	{
		loadVarToMap(env.wrapperOpenclTemplate,currPool);
		updateVariable(currPool,pool,this);
	}
	
	// replace key starting with char $ in "env.wrapperHeaderTemplate" file with actual values and store result in "wrapper_header.cc"
	replaceWithVariablesValue(env.wrapperHeaderTemplate,"wrapper_header.cc",pool);
	
	// replace key starting with char $ in "env.wrapperInfTemplate" file with actual values and store result in "wrapper_inf.cc"
	replaceWithVariablesValue(env.wrapperInfTemplate,"wrapper_inf.cc",pool);
	
	if(configure->exist("CPU"))
		replaceWithVariablesValue(env.wrapperCpuTemplate,"wrapper_cpu.cc",pool);
	if(configure->exist("CUDA"))
		replaceWithVariablesValue(env.wrapperCudaTemplate,"wrapper_cuda.cc",pool);
	if(configure->exist("OPENCL"))
		replaceWithVariablesValue(env.wrapperOpenclTemplate,"wrapper_opencl.cc",pool);

    //merge
	string wrapperFile=(*pool)["INWH2"];
	ofstream c;
	c.open(wrapperFile.c_str(),ios::out);
	c.close();
	mergeFile(wrapperFile,"wrapper_header.cc");
	
	if(configure->exist("CPU"))
		mergeFile(wrapperFile,"wrapper_cpu.cc");
		
	if(configure->exist("CUDA"))
		mergeFile(wrapperFile,"wrapper_cuda.cc");
		
	if(configure->exist("OPENCL"))
		mergeFile(wrapperFile,"wrapper_opencl.cc");
		
	mergeFile(wrapperFile,"wrapper_inf.cc");

	if(env.verboseLevel>=3)
		showMap(pool,"Wrapper Generation for "+(*pool)["IN1"]);
}


void Component::handle_constraints_pass(){

	//Direct command low level components, because of the relatively high level of view

	//First, evaluate all constraints, of course, dynamic constraints will do nothing
	for(auto it=impls.begin();it!=impls.end();++it)
	{
		//if one of the constraints for one impl not hold
		if( !it->second->constraints.eval_constraints() ){
			//if impl is in configuration, remove it,
			//later add the logic to move the next constraints-satisfied impl
			//of the same type to configuration

			assertx(configure->get(it->second->type.getType())!=0, "implementation type not in configure!");
			if (it->second  == configure->get(it->second->type.getType()) ) 
				configure->set(it->second->type.getType(), 0);
			
			
		}
	}

	

}
