#ifndef OPCC2_
#define OPCC2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Opencl codelet core binding statement
*  @details This class is responsible for generating opencl codelet core binding statement, for example: 'cl.opencl_func = scal_opencl_func_wrapper ;' (assume vector_scal is interface name)
*/
class OPCC2 : public Helper
{
	public:
		/** Calculate variable OPCC2 from Intermediate Representation. Calculated variable OPCC2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

