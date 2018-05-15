#ifndef CLF2_
#define CLF2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Codelet finish statement
*  @details This class is responsible for generating codelet finish statement, for example: 'clFinish(queue_vector_scal);' (assume vector_scal is interface name)
*/
class CLF2 : public Helper
{
	public:
		/** Calculate variable CLF2 from Intermediate Representation. Calculated variable CLF2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

