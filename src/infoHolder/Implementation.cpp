
#include <Implementation.h>
#include <Helper.h>
#include <helperFactory.h>
#include <assert.h>


using namespace std;


Implementation::Implementation(Node *tree_):tree(tree_),impPath(""),cmpList(new CompileStmtList()),depCompList(new DepCompList()),cdltInfo(0)
{
	init();
}

Implementation::Implementation(Node *tree_, string impPath_):tree(tree_),impPath(impPath_),cmpList(new CompileStmtList()),depCompList(new DepCompList()),cdltInfo(0)
{
	init();
}


// To initialize implementation structure from the XML (Node *)
void Implementation::init()
{
	DEBUG_METHOD_ENTRY("init()") // used for debugging purposes to trace problems...
	
	updateName();
	
	updateSourceFileName();
	
	updateInfName();
	
	//update type
	updateType();
		
	//update tmplate flag
	updateTemplateInfo();
	
	//update compile stmt
	updateCompileStmt();
	
	//if type is OPENCL, then update codelet info
	updateCodeletInfo();
	
	//update dependency
	updateCompDepList();

	//update static constraints
	updateConstraints();
}

/** Extract implementation name from syntax tree */
void Implementation::updateName()
{
	Helper *helper=helperFactory::createHelper("IMNP1");
	name="NF";
	if(helper)
	{
		name = trimSpaces(helper->getResult(tree));
		delete helper;
	}
	
}

/** Extract source file name from syntax tree */
void Implementation::updateSourceFileName()
{
	Helper *helper=helperFactory::createHelper("SN1");
	source="NF";
	if(helper)
	{
		source = trimSpaces(helper->getResult(tree));
		delete helper;
	}
}

/** Extract provided interface name from syntax tree */
void Implementation::updateInfName()
{
	Helper *helper=helperFactory::createHelper("PIFN1");
	infName="NF";
	if(helper)
	{
		infName= trimSpaces(helper->getResult(tree));
		delete helper;
	}
}

/** Extract hardware information(e.g. CUDA, CPU, OPENCL) from syntax tree */
void Implementation::updateType()
{
	Helper *helper=helperFactory::createHelper("TYPE1");
	string result="NF";
	if(helper)
	{
		result = trimSpaces(helper->getResult(tree));
		delete helper;
	}
	type.setType(result);
}

/** Extract template info from syntax tree */
void Implementation::updateTemplateInfo()
{
	Helper *helper=helperFactory::createHelper("TPLT");
	tpltType="NF";
	if(helper)
	{
		tpltType = trimSpaces(helper->getResult(tree));
		delete helper;
	}
}

//OPT: can direct have CompileStmtList initialized from tree
void Implementation::updateCompileStmt()
{
	// it it is defined as template or include then dont need to add compile statements in Makefile.
	if(capitalizeString(tpltType) == "TEMPLATE" || capitalizeString(tpltType) == "INCLUDE") 
	{   }
	else
	{
		CompileStmtList *cmp;	
		cmp = new CompileStmtList(tree,impPath);
		cmpList->add(cmp);	
	}
}

/** Extract Codelet info(only for Opencl Component) from syntax tree */
void Implementation::updateCodeletInfo()
{
	if(type.getType()=="OPENCL")
	{
		cdltInfo=new CodeletInfo(tree);
	}
}

/** Extract dependent component info from syntax tree */
void Implementation::updateCompDepList()
{
	Helper *helper=helperFactory::createHelper("RIN1");
	string result="NF";
	if(helper)
	{
		result = helper->getResult(tree);
		delete helper;
	}
	
	//update dep
	if(result!="")
	{
		istringstream iss(result);
		string name;
		string xmlFile;
		DepComp *p;
		while(iss.good())
		{
			if(iss.peek()==13)
				break;
			iss>>name;
			iss>>xmlFile;
			p=new DepComp(name,xmlFile);
			depCompList->add(p);
		}
	}
    //depCompList->show();
}

void Implementation::updateConstraints()
{
	Helper *helper=helperFactory::createHelper("CONSTRAINTS");
	assert(helper!=0);
	constraints=helper->get_result(tree);
	//constraints.print_me();
}


/**  Print info of Implementation, used for verbose mode. */
void Implementation::printMe()
{
	DEBUG_METHOD_ENTRY("printMe") // used for debugging purposes to trace problems...
	
	cout<<endl<<"Implementation name: "<<name<<endl;
	cout<<"Platform: "<<type.getType()<<endl;
	cout<<"Provided Interface name: "<<infName <<endl;
	cout<<"Implementation path: "<<impPath<<endl;
	
	cout<<"Template: "<<(tpltType=="template"?"true":"false") <<endl;
	cout<<"Compile Statement: "<<endl;
	cmpList->show();
	if(cdltInfo)
		cdltInfo->printMe();
	
}

