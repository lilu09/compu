#ifndef SCLBO2_
#define SCLBO2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Structure name that generates object name for structure that contains a struct starpu_codelet and a bool variable
*  @details This class is responsible for generating object name for a structure that contains a struct starpu_codelet and a bool variable
*/
class SCLBO2 : public Helper
{
	public:
		/** Calculate variable SCLBO2 from Intermediate Representation. Calculated variable SCLBO2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

