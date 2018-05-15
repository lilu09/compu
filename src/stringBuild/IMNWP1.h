#ifndef IMNWP1_
#define IMNWP1_

#include <string>
#include <Helper.h>



/** @addtogroup group5

  @{
*/

/** @brief CPU Implementation wrapper name
*  @details This class is responsible for generating CPU Implementation wrapper name , for example: 'scal_cpu_func_wrapper' (assume vector_scal is interface name)
*/
class IMNWP1 : public Helper
{
	public:
		/** Calculate variable IMNWP1 from Intermediate Representation. Calculated variable IMNWP1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

