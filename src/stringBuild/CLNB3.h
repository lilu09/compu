#ifndef CLNB3_
#define CLNB3_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet buffer number assignment
*  @details This class is responsible for generating codelet boolean name, for example: 'cl_vector_scal_init' (assume vector_scal is interface name)
*/
class CLNB3 : public Helper
{
	public:
		/** Calculate variable CLNB3 from Intermediate Representation. Calculated variable CLNB3 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

