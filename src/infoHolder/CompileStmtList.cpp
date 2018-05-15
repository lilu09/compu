
#include <iostream>
#include <CompileStmtList.h>

using namespace std;

/**  Default constructor, with nothing in it. */
CompileStmtList::CompileStmtList(): cg_compileStmtList(new CG_CompileStmtList()) 
{  }

/*!  
 * Constructor. Initialize member variables by syntax tree. This method is useful for building Intermediate Representation.
 */
CompileStmtList::CompileStmtList(Node *tree,std::string path): cg_compileStmtList(new CG_CompileStmtList(tree, path))
{  }

/*!  
 * Constructor. Initialize member variables by Intermediate Representation. 
 * This method is useful for generating code from Intermediate Representation. 
 */
CompileStmtList::CompileStmtList(EntryComponent *com): cg_compileStmtList(new CG_CompileStmtList(com))
{  }

/**  Add a statement to this list. Facade to CG_CompileStmtList::add() method */
void CompileStmtList::add(CompileStmtList *csl)
{
	DEBUG_METHOD_ENTRY("add") // used for debugging purposes to trace problems...
	
	cg_compileStmtList->add(csl);
}

/**  Add a statement list to this list. Facade to CG_CompileStmtList::add() method  */
void CompileStmtList::add(CompileStmt *cs)
{
	cg_compileStmtList->add(cs);
}

/**  Get iterator at beginning. Facade to CG_CompileStmtList::getBegin() method. */
vector<CompileStmt *>::iterator CompileStmtList::getBegin()
{
	return cg_compileStmtList->getBegin(); 
}

/**  Get iterator at end. Facade to CG_CompileStmtList::getEnd() method. */
vector<CompileStmt *>::iterator CompileStmtList::getEnd()
{
	return cg_compileStmtList->getEnd(); 
}

/**  Show what list contains. Facade to CG_CompileStmtList::show() method. */
void CompileStmtList::show()
{
	cg_compileStmtList->show();
}

/**  Get size of this compiling statement list. Facade to CG_CompileStmtList::size() method. */
int CompileStmtList::size()
{
	return cg_compileStmtList->size();
}

/**  Calcuting variable RM2. Facade to CG_CompileStmtList::getRM2() method. */
string CompileStmtList::getRM2()
{
	return cg_compileStmtList->getRM2();
}


/*!
 * Get the first statement. This method is useful for fetching linking statement since it is 
 * normally located at first in the list.
 */
CompileStmt *CompileStmtList::getFirst()
{
	DEBUG_METHOD_ENTRY("getFirst") // used for debugging purposes to trace problems...
	
	if(cg_compileStmtList->size()==0)
	   error("There is no element in CompileStmtList vector to return. Potential incorrect/missing compiler information in XML.");
	   
	return cg_compileStmtList->getBegin()[0]; 
}

