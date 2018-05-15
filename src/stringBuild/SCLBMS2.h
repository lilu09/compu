#ifndef SCLBMS2_
#define SCLBMS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet memset to ensure all fields are set to zero
*  @details This class is responsible for generating statement for codelet memset to ensure all fields are set to zero, for example: 'memset (..->cl_vector_scal..) ;' (assume vector_scal is interface name)
*/
class SCLBMS2 : public Helper
{
	public:
		/** Calculate variable SCLBMS2 from Intermediate Representation. Calculated variable SCLBMS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

