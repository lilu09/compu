#ifndef TWFA_
#define TWFA_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Cpu codelet core binding statement
*  @details This class is responsible for generating task creation loop if supported for an interface. 
*/
class TWFA : public Helper
{
	public:
		/** Calculate variable TWFA from Intermediate Representation. Calculated variable TWFA is used for replacement in template file.*/
		std::string getResult(Component *com);		
};
/**	@} 
*/
#endif

