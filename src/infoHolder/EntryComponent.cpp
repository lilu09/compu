#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <EntryComponent.h>
#include <EnvVar.h>
#include <Node.h>
#include <methods.h>
#include <Implementation.h>
#include <CompileStmt.h>
#include <ComConfig.h>

using namespace std;

extern EnvVar env;

/** Parse entry component's XML file, and build Intermediate Representation for EntryComponent. */
void EntryComponent::parse(string fileName)
{
	DEBUG_METHOD_ENTRY("parse") // used for debugging purposes to trace problems...
	
	Node *tree;
	buildComponentTree(fileName, tree);
	//build IR for EntryComponent
	impl=new Implementation(tree);
}


/** Build intermediate representation of dependent component, if defaultValue is set to true, then for each type, the first added component will become the default component in the component configuration*/
void EntryComponent::buildIR(bool defaultValue)
{
	DEBUG_METHOD_ENTRY("buildIR") // used for debugging purposes to trace problems...	
	
        defaultFlag=defaultValue;
	Node *aTree;
	vector<DepComp *>::iterator it;
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();it++)
	{
		 buildComponentTree( (*it)->xmlName, aTree);
		 (*it)->com = new Component(aTree, defaultFlag);
		 
		 // if specified globally usage of history based performance models then set for each component
		 if(env.useHistoryModels)
		 	(*it)->com->intfc->useHistoryModels = true;
		 
		 if(env.disableCPU)
		 	(*it)->com->intfc->disableCPU = true;	
		 
		 if(env.disableCUDA)
		 	(*it)->com->intfc->disableCUDA = true;		
		 
		 if(env.disableOpenCL)
		 	(*it)->com->intfc->disableOpenCL = true;		
	}
	
	// check for enabling/disabling a backend
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();it++)
	{
		if((*it)->com->intfc->disableCPU)
		 	(*it)->com->configure->set("CPU",0);
		 
		 if((*it)->com->intfc->disableCUDA)
		 	(*it)->com->configure->set("CUDA",0);
		 
		 if((*it)->com->intfc->disableOpenCL)
		 	(*it)->com->configure->set("OPENCL",0);
		 	
		 if( !(*it)->com->configure->exist("CPU") && !(*it)->com->configure->exist("CUDA") && !(*it)->com->configure->exist("OPENCL") )
		 	error("No implementation available for interface: "+(*it)->com->intfc->name+".  There should be atleast one backend implementation available to generate the code for a component");	
	}
	
	
//	updateLinkStmt();
	if(env.verboseLevel>=1)
		printIR();
}


void EntryComponent::handle_entry_component_constraints()
{
}


void EntryComponent::handle_constraints_in_IR(){
	//handle_static_constraints_in_IR(); //no need to separate them, they are treated uniformally
	//handle_dynamic_constraints_in_IR(); 
	
	handle_entry_component_constraints();

	for (auto it = impl->depCompList->getBegin(); it!=impl->depCompList->getEnd(); ++it ) {
		(*it)->com->handle_constraints_pass();
	}
	

}

void handle_static_constraints_in_IR(){
}
void handle_dynamic_constraints_in_IR(){
}


bool EntryComponent::hasOpenMPImpl()
{
	//update dependency in Entry Component
	vector<DepComp *>::iterator it;
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();++it)
	{
		if( (*it)->com->hasOpenMPImpl() )
			return true;
	}
	return false;
}

std::string EntryComponent::getOutputName()
{
	//find link statement
	CompileStmt *linkStmt=0;
	vector<CompileStmt *>::iterator it,it2;
	for(it=impl->cmpList->getBegin();it!=impl->cmpList->getEnd();++it)
	{
		if ((*it)->type == "link")
		{
			return (*it)->obj;
		}
	}

	warn("Problems in makefile generation. No linking statement found in XML files!");
	return "NF";
}

/** Update link statement, since link statement can not be built until other compile statements has been added to Intermediate Representation. */
void EntryComponent::updateLinkStmt()
{
	DEBUG_METHOD_ENTRY("updateLinkStmt") // used for debugging purposes to trace problems...	
	
	//find link statement
	CompileStmt *linkStmt=0;
	vector<CompileStmt *>::iterator it,it2;
	for(it=impl->cmpList->getBegin();it!=impl->cmpList->getEnd();++it)
	{
		if ((*it)->type == "link")
		{
			linkStmt=(*it);
			break;
		}
	}


	//update dependency in Entry Component
	if(linkStmt)
	{
		for(it=impl->cmpList->getBegin();it!=impl->cmpList->getEnd();++it)
		{
			if ((*it)->type != "link")
			{
				linkStmt->dep += ((*it)->validCompileStmt)? ( " "+(*it)->obj ) : "";
			}
		}
		
		//update dependency in Entry Component
		vector<DepComp *>::iterator it3;
		for(it3=impl->depCompList->getBegin();it3!=impl->depCompList->getEnd();it3++)
		{
			if( (*it3)->com->configure->get("CPU") )
			{
				for(it2=(*it3)->com->configure->get("CPU")->cmpList->getBegin();it2!=(*it3)->com->configure->get("CPU")->cmpList->getEnd();++it2)
				{
					linkStmt->dep += ((*it2)->validCompileStmt)? ( " "+(*it2)->obj ) : "";
				}
			}
			if( (*it3)->com->configure->get("CUDA") )
			{
				for(it2=(*it3)->com->configure->get("CUDA")->cmpList->getBegin();it2!=(*it3)->com->configure->get("CUDA")->cmpList->getEnd();++it2)
				{
					linkStmt->dep += ((*it2)->validCompileStmt)? (" "+(*it2)->obj ) : "";
				}
			}
			if( (*it3)->com->configure->get("OPENCL") )
			{
				for(it2=(*it3)->com->configure->get("OPENCL")->cmpList->getBegin();it2!=(*it3)->com->configure->get("OPENCL")->cmpList->getEnd();++it2)
				{
					linkStmt->dep += ((*it2)->validCompileStmt)? ( " "+(*it2)->obj ) : "";
				}
			}
		}
	
		linkStmt->setStmt();
	}
}


/** Print all necessary info of EntryComponent and dependent Components, used for verbose mode. */
void EntryComponent::printIR()
{
	DEBUG_METHOD_ENTRY("printIR") // used for debugging purposes to trace problems...	
	
	if(env.verboseLevel>=1)
		printRelation();
	if(env.verboseLevel>=2)
		printComponent();
}


/** Print an overview of Component dependency tree, used for verbose mode. */
void EntryComponent::printRelation()
{
	DEBUG_METHOD_ENTRY("printRelation") // used for debugging purposes to trace problems...	
	
	cout<<"/************************************************/"<<endl;
	cout<<endl<<"Component Dependency Tree: "<<endl;
	string space="  ",root="+",leaf="-",entry="Entry Component: ", com="Component:";
	//print Entry Component
	cout<<space<<root<<entry<<impl->name<<endl;
	//print Component recursively
	vector<DepComp *>::iterator it;
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();it++)
	{
		space=space+"  ";
		(*it)->com->printName(space);
	}
    cout<<"/************************************************/"<<endl<<endl;
}


/** Print info of EntryComponent's dependent Components, used for verbose mode. */
void EntryComponent::printComponent()
{
	DEBUG_METHOD_ENTRY("printComponent") // used for debugging purposes to trace problems...	
	
	//print Entry Component
     printMe();
	//print Component
	
	vector<DepComp *>::iterator it;
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();it++)
	{
		(*it)->com->printMe();
	}
	
}


/** Print info of EntryComponent, used for verbose mode.*/
void EntryComponent::printMe()
{
	DEBUG_METHOD_ENTRY("printMe") // used for debugging purposes to trace problems...	
	
	cout<<"/************************************************/"<<endl;
	cout<<endl<<"Entry Component: "<<impl->name<<endl;
	impl->printMe();

	cout<<"/************************************************/"<<endl<<endl;
}


/** generate header file "peppher.h"*/
void EntryComponent::generateHeader()
{
	DEBUG_METHOD_ENTRY("generateHeader") // used for debugging purposes to trace problems...		
	
	map <string, string> *pool=new map <string, string>;
	map <string, string> *currPool=new map <string, string>;
	
	//calculate
	loadVarToMap(env.mainWrapperTemplate,currPool);
	updateVariable(currPool,pool,this);

	//generate header
	string tmpFile="peppher_temp" + env.wrapperFilesExt;
	replaceWithVariablesValue(env.mainWrapperTemplate,tmpFile,pool); // replace key starting with char $ in "env.mainWrapperTemplate" file with actual values and store result in "tmpFile"
	replaceWithEnterKey(tmpFile,"peppher" + env.wrapperFilesExt,"@"); // replace @ char in "tmpFile" file with <Enter> key and save the output in "peppher.h" file.
	remove(tmpFile.c_str());

	if(env.verboseLevel>=3)
		showMap(pool,"Header Generation");
}


/** generate wrapper for every interface parsed*/
void EntryComponent::generateWrapper()
{
	DEBUG_METHOD_ENTRY("generateWrapper") // used for debugging purposes to trace problems...		
	
	//call subcomponent the same method
	vector<DepComp *>::iterator it;
	for(it=impl->depCompList->getBegin();it!=impl->depCompList->getEnd();it++)
	{
		(*it)->com->generateWrapper();
	}
}



/** generate makefile*/
void EntryComponent::generateMakefile()
{
	DEBUG_METHOD_ENTRY("generateMakefile") // used for debugging purposes to trace problems...		
	
	updateLinkStmt();
	map <string, string> *pool=new map <string, string>;
	map <string, string> *currPool=new map <string, string>;

	loadVarToMap(env.makefileTemplate,currPool,'!');
	updateVariable(currPool,pool,this);
	

	//code generate
	string tmpFile="makefile.cc";
	
	replaceWithVariablesValue(env.makefileTemplate,tmpFile,pool,'!'); // replace key starting with char $ in "env.makefileTemplate" file with actual values and store result in "tmpFile"

	//deal with new line and tab
	replaceWithEnterTabKey(tmpFile, "makefile"); // replaces @ent and @tab in "tmpFile" with Enter and Tab key respectively and store result in "makefile" file
	remove(tmpFile.c_str());

	if(env.verboseLevel>=3)
		showMap(pool,"Makefile Generation");
	
}

