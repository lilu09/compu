#ifndef CLNB2_
#define CLNB2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet buffer number assignment
*  @details This class is responsible for generating codelet boolean name, for example: 'cl_vector_scal_init' (assume vector_scal is interface name)
*/
class CLNB2 : public Helper
{
	public:
		/** Calculate variable CLNB2 from Intermediate Representation. Calculated variable CLNB2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

