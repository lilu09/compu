#ifndef SCLB3_
#define SCLB3_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Structure name that contains a struct starpu_codelet and a bool variable
*  @details This class is responsible for generating structure name that contains a struct starpu_codelet and a bool variable
*/
class SCLB3 : public Helper
{
	public:
		/** Calculate variable SCLB3 from Intermediate Representation. Calculated variable SCLB3 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

