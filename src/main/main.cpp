#include <cstdlib>
#include <iostream>
#include <string>
#include <map>
#include <main.h>
#include <configuration.h>
#include <init.h>
#include <EntryComponent.h>
#include <ComConfig.h>


using namespace std;

int main(int argC, char** argV)
{
	
	sysInit(&env,argC,argV);
	
	//load Parse Tree
	EntryComponent mainFunc;
	mainFunc.parse(env.entry);
    
	//build IR
	mainFunc.buildIR(TRUE);

	//handle static and dynamic constraint of each interface and implementation
	mainFunc.handle_constraints_in_IR();

	//Generate Code
        mainFunc.generateWrapper();

	mainFunc.generateHeader();

	mainFunc.generateMakefile();

	
}



/*                         Old way to change IR, no nice facility, only as reference               */
/* *********************************************************************************************** */
/* 
	#ifdef PASS_ENABLE
	// Passes specificly for sorting example

	 //  how to change default implementation

		//step1: get pointer to defaulat implementation
		vector<DepItem *>::iterator it=mainFunc.impl->depList->getBegin();
		string cpu="CPU";
		cout<<"Default implementation:	";
		cout<<(*it)->com->configure->get(cpu)->name<<endl;

		//step 2: get pointer to a non-default implementation
		cout<<"all CPU implementations available: ";
		multimap<string, Implementation *>::iterator itCpu;
		for (itCpu=(*it)->com->impls.equal_range(cpu).first; 
		itCpu!=(*it)->com->impls.equal_range(cpu).second; ++itCpu)
			cout << " " << (*itCpu).second->name;
		cout<<endl;

		//step 3: change default CPU implementation from bubble sort to insertion sort
		for (itCpu=(*it)->com->impls.equal_range(cpu).first; 
		itCpu!=(*it)->com->impls.equal_range(cpu).second; ++itCpu)
			if( (*itCpu).second->name=="insert")
				(*it)->com->configure->set("CPU",(*itCpu).second);
		cout<<"Default implementation:	";
		cout<<(*it)->com->configure->get(cpu)->name<<endl;

	// how to disable cuda platform
	(*it)->com->configure->set("CUDA",0);
	cout<<"CUDA: "<<(*it)->com->configure->get("CUDA")<<endl;
	#endif
*/
/* *********************************************************************************************** */


