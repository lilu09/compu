#ifndef INWC2_
#define INWC2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Capitalized interface name wrapper
*  @details This class is responsible for generating Capitalized interface name wrapper, for example: 'VECTOR_SCALE_WRAPPER' (assume vector_scal is interface name)
*/
class INWC2 : public Helper
{
	public:
		/** Calculate variable INWC2 from Intermediate Representation. Calculated variable INWC2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

