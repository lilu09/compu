#ifndef HBPMA2_
#define HBPMA2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief codelet name
*  @details This class is responsible for generating starpu_perfmodel assignment statements for symbol, type
*/
class HBPMA2 : public Helper
{
	public:
		/** Calculate variable HBPMA2 from Intermediate Representation. Calculated variable HBPMA2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

