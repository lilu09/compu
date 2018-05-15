#ifndef COMPILESTMTLIST_
#define COMPILESTMTLIST_

#include <vector>
#include <CompileStmt.h>
#include <cg_helpers/CG_CompileStmtList.h>


/** @addtogroup group2
*
* @{
*/
/** @brief  Compile statement List, container for CompileStmt*/

class CompileStmtList
{
public: 
	/**  Default constructor, with nothing in it. */
	CompileStmtList();
	
	/*!  
	 * Constructor. Initialize member variables by syntax tree. This method is useful for building Intermediate Representation.
	 */
	CompileStmtList(Node *tree,std::string path);
	
	/*!  
	 * Constructor. Initialize member variables by Intermediate Representation. 
	 * This method is useful for generating code from Intermediate Representation. 
	 */
	CompileStmtList(EntryComponent *com); // used for calculating RM2
	
	/**  Add a statement to this list. Facade to CG_CompileStmtList::add() method */
	void add(CompileStmt *cs);
	
	/**  Add a statement list to this list. Facade to CG_CompileStmtList::add() method  */
	void add(CompileStmtList *csl);
	
	/**  Get iterator at beginning. Facade to CG_CompileStmtList::getBegin() method. */
	std::vector<CompileStmt *>::iterator getBegin();
	
	/**  Get iterator at end. Facade to CG_CompileStmtList::getEnd() method. */
	std::vector<CompileStmt *>::iterator getEnd();
	
	/**  Show what list contains. Facade to CG_CompileStmtList::show() method. */
	void show();
	
	/**  Get size of this compiling statement list. Facade to CG_CompileStmtList::size() method. */
	int size();
	
	/**  Calcuting variable RM2. Facade to CG_CompileStmtList::getRM2() method. */
	std::string getRM2();
	
	/*!
	 * Get the first statement. This method is useful for fetching linking statement since it is 
	 * normally located at first in the list.
	 */
	CompileStmt *getFirst();

private:	

	/**  Handler to code generation class. */
	CG_CompileStmtList *cg_compileStmtList;
	
};

/** @} */
#endif

