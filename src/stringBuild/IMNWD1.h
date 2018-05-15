#ifndef IMNWD1_
#define IMNWD1_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Implementation wrapper name of CUDA
*  @details This class is responsible for generating Implementation wrapper name of CUDA, for example: 'scal_cuda_func_wrapper' (assume vector_scal is interface name)
*/
class IMNWD1 : public Helper
{
	public:
		/** Calculate variable IMNWD1 from Intermediate Representation. Calculated variable IMNWD1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

