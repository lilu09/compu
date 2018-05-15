#ifndef CLRL2_
#define CLRL2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Codelet running location statement
*  @details This class is responsible for generating codelet running location statement, for example: 'cl_vector_scal2.where = 0|STARPU_CPU;' (assume vector_scal is interface name)
*/
class CLRL2 : public Helper
{
	public:
		/** Calculate variable CLRL2 from Intermediate Representation. Calculated variable CLRL2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

