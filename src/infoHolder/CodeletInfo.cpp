#include <iostream>
#include <CodeletInfo.h>
#include <Helper.h>
#include <helperFactory.h>

using namespace std;


CodeletInfo::CodeletInfo():starpu_opencl_program(""),cl_kernel(""),cl_command_queue(""),kernel(""),codelet_file("")
{
	
}

CodeletInfo::CodeletInfo(Node *tree)
{
	init(tree);
}


void CodeletInfo::init(Node *tree)
{
	DEBUG_METHOD_ENTRY("init") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper("SOPN2");
	starpu_opencl_program="NF";
	if(helper)
	{
		starpu_opencl_program = helper->getResult(tree);
		delete helper;
	}
	
	helper=helperFactory::createHelper("CKN2");
	cl_kernel="NF";
	if(helper)
	{
		cl_kernel = helper->getResult(tree);
		delete helper;
	}

	helper=helperFactory::createHelper("CCQN2");
	cl_command_queue="NF";
	if(helper)
	{
		cl_command_queue = helper->getResult(tree);
		delete helper;
	}

	helper=helperFactory::createHelper("LKS2");
	kernel="NF";
	if(helper)
	{
		kernel = helper->getResult(tree);
		delete helper;
	}

	helper=helperFactory::createHelper("LCLS2");
	codelet_file="NF";
	if(helper)
	{
		codelet_file = helper->getResult(tree);
		delete helper;
	}
}

void CodeletInfo::printMe()
{
	cout<<"OPENCL codelet Info: "<<endl;
	cout<<"  starpu_opencl_program: "<<starpu_opencl_program <<endl;
	cout<<"  cl_kernel: "<<cl_kernel <<endl;
	cout<<"  cl_command_queue: "<<cl_command_queue<<endl;
	cout<<"  kernel: "<<kernel<<endl;
	cout<<"  codelet_file: "<<codelet_file<<endl;
}


