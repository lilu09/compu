#ifndef SCLB2_
#define SCLB2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Structure name that contains a struct starpu_codelet and a bool variable
*  @details This class is responsible for generating structure name that contains a struct starpu_codelet and a bool variable
*/
class SCLB2 : public Helper
{
	public:
		/** Calculate variable SCLB2 from Intermediate Representation. Calculated variable SCLB2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

