#ifndef LKS2_
#define LKS2_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Opencl program kernel name
*  @details This class is responsible for generating opencl program kernel name, for example: 'vector_mult_opencl' (assume vector_scal is interface name)
*/
class LKS2 : public Helper
{
	public:
		/** Calculate variable LKS2 from Syntax tree.Calculated variable LKS2 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
		/** Calculate variable LKS2 from Intermediate Representation. Calculated variable LKS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

