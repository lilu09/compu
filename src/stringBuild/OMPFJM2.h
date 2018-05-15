#ifndef OMPFJM2_
#define OMPFJM2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Loading codelet statement
*  @details This class is responsible for generating statements for using OpenMP component instead of 1 CPU for example: 'objSt_euler3d_func->cl_euler3d_func.type = STARPU_FORKJOIN;
objSt_euler3d_func->cl_euler3d_func.max_parallelism = INT_MAX'
*/
class OMPFJM2 : public Helper
{
	public:
		/** Calculate variable OMPFJM2 from Intermediate Representation. Calculated variable OMPFJM2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

