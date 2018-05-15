#ifndef INWH2_
#define INWH2_

#include <string>
#include <Helper.h>
#include <Component.h>


/** @addtogroup group5

  @{
*/

/** @brief Interface wrapper header file name
*  @details This class is responsible for generating Interface wrapper header file name, for example: 'vector_scal_wrapper.h' (assume vector_scal is interface name)
*/
class INWH2 : public Helper
{
	public:
		/** Calculate variable INWH2 from Intermediate Representation. Calculated variable INWH2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

