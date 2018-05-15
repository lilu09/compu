#ifndef CCCS2_
#define CCCS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Cpu codelet core binding statement
*  @details This class is responsible for generating statement for binding codelet with CPU components, for example: 'cl.cpu_func = scal_cpu_func_wrapper ;' 
*/
class CCCS2 : public Helper
{
	public:
		/** Calculate variable CCCS2 from Intermediate Representation. Calculated variable CCCS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

