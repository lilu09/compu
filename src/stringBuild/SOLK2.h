#ifndef SOLK2_
#define SOLK2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Starpu opencl loading kernel statement
*  @details This class is responsible for generating starpu opencl loading kernel statement, for example: 'int err = starpu_opencl_load_kernel(&kernel, &queue, &codelet, "vector_mult_opencl", devid);' (assume vector_scal is interface name)
*/
class SOLK2 : public Helper
{
	public:
		/** Calculate variable SOLK2 from Intermediate Representation. Calculated variable SOLK2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

