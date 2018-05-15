#ifndef ROPD1_
#define ROPD1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Read only parameter definition
*  @details This class is responsible for generating Read only parameter definition, for example: 'float factor;' (assume vector_scal is interface name)
*/
class ROPD1 : public Helper
{
	public:
		/** Calculate variable ROPD1 from Intermediate Representation. Calculated variable ROPD1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

