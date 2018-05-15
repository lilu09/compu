#ifndef RIN1_
#define RIN1_

#include <string>

#include <Helper.h>
#include <Node.h>

/** @addtogroup group5

  @{
*/

/** @brief Required interface name and filename
*  @details This class is responsible for generating required interface name and filename, for example: "vector_scal vector_scal.xml" (assume vector_scal is interface name)
*/
class RIN1 : public Helper
{
	public:
		/** Calculate variable RIN1 from Syntax tree.Calculated variable RIN1 is used for building Intermediate Representation.*/
	    std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

