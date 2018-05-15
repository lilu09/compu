#ifndef SRL2_
#define SRL2_

#include <Helper.h>
#include <string>



/** @addtogroup group5

  @{
*/

/** @brief StarPU running location
*  @details This class is responsible for generating StarPU running location, for example:  'STARPU_CPU | STARPU_CUDA' (assume vector_scal is interface name)
*/
class SRL2 : public Helper
{
	public:
		/** Calculate variable SRL2 from Intermediate Representation. Calculated variable SRL2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

