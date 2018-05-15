#ifndef COMPILESTMT_
#define COMPILESTMT_

#include <string>
#include <Node.h>


/** @addtogroup group2
*
* @{
*/

/** @brief  Compile statement. */
class CompileStmt
{
public:
	
	/**  Default constructor, empty function. */
	CompileStmt();
	
	/**  Copy constructor.*/
	CompileStmt(CompileStmt *cmp);
	
	/*!  
	 * Constructor. This method initialize all member variables from syntax tree(tree). 
	 * First argument(target) is position of Element which store a single compiling statement in syntax 
	 * tree, since one syntax tree may contains several compile statements. 
	 */
	CompileStmt(Node *target,Node *tree, std::string impPath);
	
	/*! 
	 * Set member variable. Meta is path relative to target, and target is pointer to Element which store 
	 * a single compile statement in syntax tree, since one syntax tree may contains several compile statements.
	 */
	void setValue(std::string &var, std::string meta,Node *target);
	
	/**  Set member variable stmt, which is complete compile command used in Makefile.*/
	void setStmt();
	
	void show();
	

	/**  Target name, used in Makefile. */
	std::string obj;
	
	/**  Source file path, necessary for compile command used in Makefile. */
	std::string path;
	
	/**  Files that target depend, used in Makefile. */
	std::string dep;
	
	/**  Compiler used to compile source files, used in Makefile. */
	std::string compiler;
	
	/**  Flag used to compile source files, used in Makefile.*/
	std::string flag;
	
	/**  Complete compiling command, used in Makefile.*/
	std::string stmt;
	
	/**  This variable shows whether the whole class represents a linking statement or not.*/
	std::string type;
	
	/** To mark whether the CompileStmt is a valid one that can be used for makefile generation */
	bool validCompileStmt;
	
};

/** @} */
#endif

