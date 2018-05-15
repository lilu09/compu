#ifndef INCSU_
#define INCSU_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Inclusion of CUDA Implementation file.
*  @details This class is responsible for generating statement of inclusion of CUDA Implementation file, for example: ' #include <vector_scal_cuda.c" '. This variable is only used if CUDA implementation contains template.
*/
class INCSU : public Helper
{
	public:
		/** Calculate variable INCSU from Intermediate Representation. Calculated variable INCSU is used for replacement in template file.*/
	    std::string getResult(Component *tree);
};
/**	@} 
*/
#endif

