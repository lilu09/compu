#ifndef EXTS_
#define EXTS_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Extern Statement for CPU
*  @details This class is responsible for generating Extern Statement for CPU, for example: 'extern void vector_scal_cpu()'. This statement should be erased when template is used.
*/
class EXTS : public Helper
{
	public:
		/** Calculate variable EXTS from Intermediate Representation. Calculated variable EXTS is used for replacement in non-template CPU implementation.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

