#ifndef LCLSC2_
#define LCLSC2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Loading codelet statement
*  @details This class is responsible for generating loading codelet statement, for example: 'int i = starpu_opencl_load_opencl_from_file("vector_minus_opencl_codelet.cl",&codelet);' (assume vector_scal is interface name)
*/
class LCLSC2 : public Helper
{
	public:
		/** Calculate variable LCLSC2 from Intermediate Representation. Calculated variable LCLSC2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

