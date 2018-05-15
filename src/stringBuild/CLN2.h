#ifndef CLN2_
#define CLN2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief codelet name
*  @details This class is responsible for generating codelet name, for example: 'cl_vector_scal' (assume vector_scal is interface name)
*/
class CLN2 : public Helper
{
	public:
		/** Calculate variable CLN2 from Intermediate Representation. Calculated variable CLN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

