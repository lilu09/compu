#ifndef ROAA2_
#define ROAA2_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Read only parameter assignment
*  @details This class is responsible for generating read only parameter assignment statement, read only parameter means non-pointer parameter, for example: 'arg.factor=factor;' (assume vector_scal is interface name)
*/
class ROAA2 : public Helper
{
	public:
		/** Calculate variable ROAA2 from Intermediate Representation. Calculated variable ROAA2 is used for replacement in template file.*/
		std::string getResult(Component *com);

};
/**	@} 
*/
#endif

