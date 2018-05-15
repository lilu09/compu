#ifndef URBPM1_
#define URBPM1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Template parameter types in an interface.
*  @details This class is responsible for returning whether to use regression based performance models or not. */
class URBPM1 : public Helper
{
	public:
		/** Calculate variable UHBPM1 from Intermediate Representation. Calculated variable UHBPM1 is used for deciding usage of regression based performance models.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

