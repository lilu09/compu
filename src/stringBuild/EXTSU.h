#ifndef EXTSU_
#define EXTSU_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Extern Statement for CUDA
*  @details This class is responsible for generating Extern Statement for CUDA, for example: 'extern void vector_scal_cpu()'. This statement should be erased when template is used.
*/
class EXTSU : public Helper
{
	public:
		/** Calculate variable EXTS from Intermediate Representation. Calculated variable EXTS is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

