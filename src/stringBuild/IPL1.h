#ifndef IPL1_
#define IPL1_

#include <string>
#include <Helper.h>


/** @addtogroup group5

  @{
*/

/** @brief Interface parameter list
*  @details This class is responsible for generating Interface parameter list, for example: 'float *arr, unsigned size, float factor' (assume vector_scal is interface name)
*/
class IPL1 : public Helper
{
	public:
		/** Calculate variable IPL1 from Intermediate Representation. Calculated variable IPL1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

