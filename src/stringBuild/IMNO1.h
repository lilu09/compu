#ifndef IMNO1_
#define IMNO1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Implementation name of OPENCL
*  @details This class is responsible for generating Implementation name of OPENCL, for example: 'scal_opencl_func' (assume vector_scal is interface name)
*/
class IMNO1 : public Helper
{
	public:
		/** Calculate variable IMNO1 from Intermediate Representation. Calculated variable IMNO1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

