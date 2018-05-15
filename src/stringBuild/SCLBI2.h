#ifndef SCLBI2_
#define SCLBI2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet buffer interger (bool) initialization
*  @details This class is responsible for generating codelet integer (boolean) initialization, for example: 'cl_vector_scal_init = 0;' (assume vector_scal is interface name)
*/
class SCLBI2 : public Helper
{
	public:
		/** Calculate variable SCLBI2 from Intermediate Representation. Calculated variable SCLBI2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

