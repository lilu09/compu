#ifndef IMPA1_
#define IMPA1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief path of all implementations for the same interface 
*  @details This class is responsible for generating path of all implementations for the same interface, for example: "./vector_scal/" (assume vector_scal is interface name)
*/
class IMPA1 : public Helper
{
	public:
		/** extract implementation path from a syntax tree of interface kind*/
		std::string getResult(Node *tree);
		
};
/**	@} 
*/
#endif

