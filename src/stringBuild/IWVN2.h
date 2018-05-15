#ifndef IWVN2_
#define IWVN2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Independent write-access variable number
*  @details This class is responsible for generating independent write-access variable number, this number determines how many data handles(StarPU structure) should be created, for example: '1' (assume vector_scal is interface name)
*/
class IWVN2 : public Helper
{
	public:
		/** Calculate variable IWVN2 from Intermediate Representation. Calculated variable IWVN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

