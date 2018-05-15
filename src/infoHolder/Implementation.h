#ifndef IMPLEMENTATION_
#define IMPLEMENTATION_

#include <Node.h>
#include <CompileStmtList.h>
#include <DepCompList.h>
#include <CodeletInfo.h>
#include <ImplType.h>
#include <Constraints.h>
/** @addtogroup group2
*
* @{
*/
/** @brief  Intermediate Representation for a single implementation */
class Implementation
{
public:
	/** Initialize an Implementation(Intermediate Representation) by a syntax tree. This method is useful for building Intermediate Representation. */
	Implementation(Node *tree_);
	
	/** Initialize an Implementation(Intermediate Representation) by a syntax tree of implementation kind, and path info(Where implementations locate), which is used for compile command generation. */
	Implementation(Node *tree_, std::string impPath_);
	
    /** Stub for all constructors*/
	void init();
	
	/** Extract implementation name from syntax tree passed by contructor*/
	void updateName();
	
	/** Extract source file name from syntax tree passed by contructor*/
	void updateSourceFileName();
	
	/** Extract provided interface name from syntax tree passed by contructor*/
	void updateInfName();
	
	/** Extract hardware information(e.g. CUDA) from syntax tree passed by contructor*/
	void updateType();
	
	/** Extract template info from syntax tree passed by contructor*/
	void updateTemplateInfo();
	
	/** Extract compilation commands from syntax tree passed by contructor*/
	void updateCompileStmt();
	
	/** Extract Codelet info(only for Opencl Component) from syntax tree passed by contructor*/
	void updateCodeletInfo();
	
	/** Extract dependent component info from syntax tree passed by contructor*/
	void updateCompDepList();

	void updateConstraints();

	
	/**  Print info of Implementation, used for verbose mode. */
	void printMe();
	
	/**  Saved tree passed from constructor. This is useful when later extension is needed.*/
	Node *tree;
	
	/** Implementation name */
	std::string name;
	
	/** Provided interface name */
	std::string infName;
	
	/**  Implementation path, used for makefile generation.*/
	std::string impPath;
	
	/** Source file name */
	std::string source;
	
	/** This member variable shows if implementation is of  template type. */
	std::string tpltType;
	
	/**  Compile statement list, used for makefile generation. */
	CompileStmtList *cmpList;
	
	/**  Platform type, such as "CPU", "CUDA",etc. */
	ImplType type;
	
	/**  Codelet info, only used when ImplType is "OPENCL".*/
	CodeletInfo *cdltInfo;
	
	/**  Dependent component list.*/
	DepCompList *depCompList;

	/**  Static and dynamic constraint list */
	Constraints constraints;
};
/** @} */
#endif

