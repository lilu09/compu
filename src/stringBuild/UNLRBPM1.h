#ifndef UNLRBPM1_
#define UNLRBPM1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Template parameter types in an interface.
*  @details This class is responsible for returning whether to use non-linear regression based performance models or not. */
class UNLRBPM1 : public Helper
{
	public:
		/** Calculate variable UHBPM1 from Intermediate Representation. Calculated variable UHBPM1 is used for deciding usage of non-linear regression based performance models.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

