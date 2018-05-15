#ifndef SORK2_
#define SORK2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Starpu opencl release kernel statement
*  @details This class is responsible for generating starpu opencl release kernel statement, for example: 'starpu_opencl_release_kernel(kernel);' (assume vector_scal is interface name)
*/
class SORK2 : public Helper
{
	public:
		/** Calculate variable SORK2 from Intermediate Representation. Calculated variable SORK2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

