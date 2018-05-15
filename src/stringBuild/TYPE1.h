#ifndef TYPE1_
#define TYPE1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Implementation type, for example: "CPU"
*  @details This class is responsible for generating implementation type, for example: "CPU" (assume vector_scal is interface name)
*/
class TYPE1 : public Helper
{
	public:
		/** Calculate variable TYPE1 from Syntax tree.Calculated variable TYPE1 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

