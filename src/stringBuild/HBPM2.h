#ifndef HBPM2_
#define HBPM2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief codelet name
*  @details This class is responsible for generating starpu_perfmodel declaration
*/
class HBPM2 : public Helper
{
	public:
		/** Calculate variable HBPM2 from Intermediate Representation. Calculated variable HBPM2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

