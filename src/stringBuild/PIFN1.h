#ifndef PIFN1_
#define PIFN1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Provided interface name
*  @details This class is responsible for generating Provided interface name, for example: 'main' (assume vector_scal is interface name)
*/
class PIFN1 : public Helper
{
	public:
		/** Calculate variable PIFN1 from Syntax tree.Calculated variable PIFN1 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

