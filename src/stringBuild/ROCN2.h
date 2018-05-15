#ifndef ROCN2_
#define ROCN2_

#include <string>
#include <Helper.h>

/** @addtogroup group5

  @{
*/

/** @brief Read only struct name
*  @details This class is responsible for generating read only struct name, read only struct contains all non-pointer parameters, for example: 'readOnlyArgs_vector_scal' (assume vector_scal is interface name)
*/
class ROCN2 : public Helper
{
	public:
		/** Calculate variable ROCN2 from Intermediate Representation. Calculated variable ROCN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

