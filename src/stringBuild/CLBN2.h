#ifndef CLBN2_
#define CLBN2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet buffer number assignment
*  @details This class is responsible for generating statement for codelet buffer number assignment, for example: 'cl_vector_scal.nbuffers = 1 ;' (assume vector_scal is interface name)
*/
class CLBN2 : public Helper
{
	public:
		/** Calculate variable CLBN2 from Intermediate Representation. Calculated variable CLBN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

