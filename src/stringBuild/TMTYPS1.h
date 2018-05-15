#ifndef TMTYPS1_
#define TMTYPS1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Template parameter types in an interface.
*  @details This class is responsible for returning template parameters in the interface file, for example: 'T, U' where T and U are generic types
*/
class TMTYPS1 : public Helper
{
	public:
		/** Calculate variable TMTYPS1 from Intermediate Representation. Calculated variable TMTYPS1 is used for calculating template parameters.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

