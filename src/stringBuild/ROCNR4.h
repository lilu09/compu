#ifndef ROCNR4_
#define ROCNR4_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Read only struct redefinition
*  @details This class is responsible for generating read only struct redefinition, for example: 'ROA_vector_scal *arg_vector_scal = malloc;' (assume vector_scal is interface name)
*/
class ROCNR4 : public Helper
{
	public:
		/** Calculate variable ROCNR4 from Intermediate Representation. Calculated variable ROCNR4 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

