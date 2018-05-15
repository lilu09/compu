#ifndef IMNP1_
#define IMNP1_

#include <Helper.h>
#include <string>

class Helper;
/** @addtogroup group5

@{
*/

/** @brief Implementation name of CPU, : 'scal_cpu_func'
*  @details This class is responsible for generating Implementation name of CPU, for example: 'scal_cpu_func' (assume vector_scal is interface name)
*/
class IMNP1 : public Helper
{
	public:
		/** get CPU implementation name from syntax tree*/
		std::string getResult(Node *tree);
		/** Calculate variable IMNP1 from Intermediate Representation. Calculated variable IMNP1 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

