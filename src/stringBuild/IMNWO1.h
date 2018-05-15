#ifndef IMNWO1_
#define IMNWO1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Opencl implementation wrapper name
*  @details This class is responsible for generating Opencl implementation wrapper name, for example: 'scal_opencl_func_wrapper' (assume vector_scal is interface name)
*/
class IMNWO1 : public Helper
{
	public:
		/** Calculate variable IMNWO1 from Intermediate Representation. Calculated variable IMNWO1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

