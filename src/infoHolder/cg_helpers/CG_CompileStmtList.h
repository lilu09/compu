#ifndef CG_COMPILESTMTLIST_
#define CG_COMPILESTMTLIST_

#include <vector>
#include <string>
#include <Node.h>
#include <CompileStmt.h>



class EntryComponent;
class CompileStmtList;
//class CompileStmt;
/** @addtogroup group2
*
* @{
*/
/** @brief  Compile statement List used for std::string calculation only, not for writing passes.*/
class CG_CompileStmtList
{
	public:
	
	/** Default, zero argument constructor */
	CG_CompileStmtList();
	
	/**  Constructor. Initialize member variables by syntax tree. This method is useful for building Intermediate Representation.*/
	CG_CompileStmtList(Node *tree,std::string path);
	
	/*! 
	 * Constructor. Initialize member variables by Intermediate Representation. This method is useful 
	 * for generating code from Intermediate Representation. 
	 */
	CG_CompileStmtList(EntryComponent *com); // used for calculating RM2
	
	/**  Stub for Constructor CG_CompileStmtList(EntryComponent *com). Do all the initialization from component */
	void init();
	
	/** returns number of compiler statements (size) contained in the list. */
	int size();
	
	/**  Show what list contains. Used for verbose mode. */
	void show();
	
	/**  Add a statement to this list. */
	void add(CompileStmt *p);
	
	/**  Add a statement list to this list. */
	void add(CompileStmtList *l);
	
	/**  Calcuting variable RM2. More detail see RM2. */
	std::string getRM2();
	
	/**  Get iterator at beginning. This method is useful for traversing this list and hide how list is implemented. */
	std::vector<CompileStmt *>::iterator getBegin();
	
	/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented. */
	std::vector<CompileStmt *>::iterator getEnd();

	/**  Container for compile statements.*/
	std::vector<CompileStmt *> list;
	
	/**  Saved EntryComponent, passed by compileStmtList_internal(EntryComponent *com);*/
	EntryComponent *com;
};

/** @} */

#endif

