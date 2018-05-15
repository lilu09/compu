#ifndef SOU2_
#define SOU2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief StarPU Opencl Unload statement
*  @details This class is responsible for generating starPU Opencl Unload statement, for example: 'starpu_opencl_unload_opencl(&codelet);' (assume vector_scal is interface name)
*/
class SOU2 : public Helper
{
	public:
		/** Calculate variable SOU2 from Intermediate Representation. Calculated variable SOU2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

