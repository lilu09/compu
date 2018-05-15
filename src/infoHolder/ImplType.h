#ifndef IMPLTYPE_
#define IMPLTYPE_

#include <string>

/** @addtogroup group2
*
* @{
*/
/** @brief  ImplType, shows which type the implementation is. There are 4 types, "CPU","CUDA","OPENCL", "OPENMP" */
class ImplType
{
public:
	/**  Default constructor, set type to NULL.*/
	ImplType();
	/**  Set type, note that there are only 3 valid value can be set: CPU, CUDA or OPENCL.*/
	void setType(std::string value);
	/**  Get type.*/
	std::string getType();
private:
	/**  Platform type, such as "NULL","CPU", "CUDA" or "OPENCL" */
	std::string type;
};

/** @} */ 

#endif

