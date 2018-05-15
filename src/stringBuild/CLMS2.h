#ifndef CLMS2_
#define CLMS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Task and handle binding statement
*  @details This class is responsible for generating task and handle binding statement, for example: 'task->buffers[0].handle = vector_handle;task->buffers[0].mode = STARPU_RW;task->buffers[1].handle = factor_handle;task->buffers[1].mode = STARPU_RW;' (assume vector_scal is interface name)
*/
class CLMS2 : public Helper
{
	public:
		/** Calculate variable CLMS2 from Intermediate Representation. Calculated variable CLMS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

