#ifndef CLTB2_
#define CLTB2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief codelet task binding statement
*  @details This class is responsible for generating codelet task binding statement, for example: 'task->cl = &cl_vector_scal;' (assume vector_scal is interface name)
*/
class CLTB2 : public Helper
{
	public:
		/** Calculate variable CLTB2 from Intermediate Representation. Calculated variable CLTB2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

