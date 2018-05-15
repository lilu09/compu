#ifndef HD2_
#define HD2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief handle declaration
*  @details This class is responsible for generating handle declaration, for example: 'starpu_data_handle_t vector_handle;starpu_data_handle_t factor_handle;' (assume vector_scal is interface name)
*/
class HD2 : public Helper
{
	public:
		/** Calculate variable HD2 from Intermediate Representation. Calculated variable HD2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

