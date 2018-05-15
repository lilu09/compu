#ifndef CUCC2_
#define CUCC2_

#include <string>
#include <Helper.h>


/** @addtogroup group5

  @{
*/

/** @brief cuda codelet core binding statement
*  @details This class is responsible for generating cuda codelet core binding statement, for example: example:'cl.cuda_func = scal_cuda_func_wrapper ;' (assume vector_scal is interface name)
*/
class CUCC2 : public Helper
{
	public:
		/** Calculate variable CUCC2 from Intermediate Representation. Calculated variable CUCC2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

