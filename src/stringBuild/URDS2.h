#ifndef URDS2_
#define URDS2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Unregistering data statement
*  @details This class is responsible for generating unregistering data statement, for example: 'starpu_data_unregister(arr_handle);starpu_data_unregister(factor_handle);' (assume vector_scal is interface name)
*/
class URDS2 : public Helper
{
	public:
		/** Calculate variable URDS2 from Intermediate Representation. Calculated variable URDS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

