#ifndef PCD1_
#define PCD1_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Used to declare peppher containers declaration
*  @details This class is responsible for generating the statement to establish whether a task is synchronous or not, for example: 'task->synchronous = 1;' 
*/
class PCD1 : public Helper
{
	public:
		/** Calculate variable TASKSYNC from Intermediate Representation. Calculated variable TASKSYNC is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

