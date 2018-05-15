#ifndef IMND1_
#define IMND1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Implementation name of CUDA
*  @details This class is responsible for generating Implementation name of CUDA, for example: 'scal_cuda_func' (assume vector_scal is interface name)
*/
class IMND1 : public Helper
{
	public:
		/** Calculate variable IMND1 from Intermediate Representation. Calculated variable IMND1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

