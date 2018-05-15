#ifndef DRS2_
#define DRS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief data register statement
*  @details This class is responsible for generating data register statement, for example: 'starpu_vector_data_register(&vector_handle, 0, (uintptr_t)vector, size, sizeof(vector)); starpu_vector_data_register(&factor_handle, 0, (uintptr_t)&factor, 1, sizeof(factor));' (assume vector_scal is interface name)
*/
class DRS2 : public Helper
{
	public:
		/** Calculate variable DRS2 from Intermediate Representation. Calculated variable DRS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

