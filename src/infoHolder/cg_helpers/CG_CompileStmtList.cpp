#include <CG_CompileStmtList.h>
#include <Node.h>
#include <Element.h>
#include <methods.h>
#include <EntryComponent.h>
#include <ComConfig.h>

using namespace std;


/** Default, zero argument constructor */
CG_CompileStmtList::CG_CompileStmtList()
{ }


/**  Constructor. Initialize member variables by syntax tree. This method is useful for building Intermediate Representation. */
CG_CompileStmtList::CG_CompileStmtList(Node *tree,string path)
{
	DEBUG_METHOD_ENTRY("CG_CompileStmtList") // used for debugging purposes to trace problems...
	
	Node *target;
	CompileStmt *tmp;
	locate(tree,env.kb["CSR"], target);
	
	if(target)
	{
		int size=target->child.size();
		for(int i=0;i<size;++i)
		{
			tmp=new CompileStmt( ( (Element *)target)->child[i], tree, path);
			add(tmp);
		}
	}
}

/*!
 * Constructor. Initialize member variables by Intermediate Representation. 
 * This method is useful for generating code from Intermediate Representation. 
 */
CG_CompileStmtList::CG_CompileStmtList(EntryComponent *com_):com(com_)
{
	init();
}

/**  Stub for Constructor CG_CompileStmtList(EntryComponent *com). Do all the initialization from component */
void CG_CompileStmtList::init()
{
	DEBUG_METHOD_ENTRY("init") // used for debugging purposes to trace problems...
	
	add (com->impl->cmpList);

	vector<DepComp *>::iterator it;
	for(it=com->impl->depCompList->getBegin();it!=com->impl->depCompList->getEnd();it++)
	{
		if( (*it)->com->configure->exist("CPU") )
			add(  (*it)->com->configure->get("CPU")->cmpList  );
		if( (*it)->com->configure->exist("CUDA") )
			add(  (*it)->com->configure->get("CUDA")->cmpList  );
		if( (*it)->com->configure->exist("OPENCL") )
			add((*it)->com->configure->get("OPENCL")->cmpList );
	}
}


/**  Add a statement to this list. */
void CG_CompileStmtList::add(CompileStmt *p)
{
	list.push_back(p);
}

/**  Add a statement list to this list. */
void CG_CompileStmtList::add(CompileStmtList *l)
{
	DEBUG_METHOD_ENTRY("add") // used for debugging purposes to trace problems...
	
	vector<CompileStmt *>::iterator it;
	
	for (it=l->getBegin(); it < l->getEnd(); it++)
		add(*it) ;
}

/** returns number of compiler statements (size) contained in the list. */
int CG_CompileStmtList::size()
{
	return list.size();
}

/**  Calcuting variable RM2. More detail see RM2. */
string CG_CompileStmtList::getRM2()
{
	DEBUG_METHOD_ENTRY("getRM2") // used for debugging purposes to trace problems...
	
	string result="",curr;
	vector<CompileStmt *>::iterator it;
	for(it=getBegin();it!=getEnd();it++)
	{
//		(*it)->show();
		if((*it)->validCompileStmt)
		{
			curr = (*it)->stmt;
			result += " "+curr;
		}
	}
	return result;
}

/**  Show what list contains. Used for verbose mode. */
void CG_CompileStmtList::show()
{
	DEBUG_METHOD_ENTRY("show") // used for debugging purposes to trace problems...
	
	vector<CompileStmt *>::iterator it;
	cout<<"     Statements Number: "<<size()<<endl;	
	for ( it=getBegin() ; it!=getEnd() ; it++ )
	{
		cout<<"    stmt: "<<(*it)->stmt<<endl;
	}
	
}

/**  Get iterator at beginning. This method is useful for traversing this list and hide how list is implemented. */
vector<CompileStmt *>::iterator CG_CompileStmtList::getBegin()
{
	return list.begin();
}

/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented. */
vector<CompileStmt *>::iterator CG_CompileStmtList::getEnd()
{
	return list.end();
}

