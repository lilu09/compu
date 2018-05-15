#ifndef METHOD_
#define METHOD_

#include <string>
#include <ParamList.h>


/** @addtogroup group2
*
* @{
*/
/** @brief  Intermediate Representation for a single method. */
class Method
{
private:
	void setPartitioningParam();
	
public:
	Method(std::string name_, std::string returnType_, Node *tree_);

	/**  Function name.*/
	std::string name;
	
	/**  Return Type. Only 'void' is valid.*/
	std::string returnType;
	
	/**  Parameter list*/
	ParamList *params;
	
	/**  Print info of Method, used for verbose mode. */
	void printMe();
	
	/**  Combine elements of Method, return complete signature. This method is used for verbose mode.*/
	std::string getSignature();
	
	/** To specify whether this method supports partitioning or not */
	bool supportPartitioning;
	
	/** the parameter that is used for deciding the task creation loop count on x-partitioning, if any */
	Param *paramXPart;
	
	/** the parameter that is used for deciding the task creation loop count on y-partitioning, if any */
	Param *paramYPart;
};
/** @} */
#endif

