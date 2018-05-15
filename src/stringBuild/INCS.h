#ifndef INCS_
#define INCS_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Inclusion of CPU Implementation file.
*  @details This class is responsible for generating statement of inclusion of CPU Implementation file, for example: ' #include <vector_scal_cpu.c" '. This variable is only used if CPU implementation contains template.
*/
class INCS : public Helper
{
	public:
		/** Calculate variable INCS from Intermediate Representation. Calculated variable INCS is used for replacement in template file.*/
	    std::string getResult(Component *tree);
};
/**	@} 
*/
#endif

