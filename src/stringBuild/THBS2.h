#ifndef THBS2_
#define THBS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Task and handle binding statement
*  @details This class is responsible for generating task and handle binding statement, for example: 'task->buffers[0].handle = vector_handle;task->buffers[0].mode = STARPU_RW;task->buffers[1].handle = factor_handle;task->buffers[1].mode = STARPU_RW;' (assume vector_scal is interface name)
*/
class THBS2 : public Helper
{
	public:
		/** Calculate variable THBS2 from Intermediate Representation. Calculated variable THBS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

