#ifndef ROATSA2_
#define ROATSA2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Read only struct task assignment
*  @details This class is responsible for generating read only struct task assignment, for example: 'task->cl_arg_size = sizeof(arg);'
*/
class ROATSA2 : public Helper
{
	public:
		/** Calculate variable ROCNR2 from Intermediate Representation. Calculated variable ROCNR2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

