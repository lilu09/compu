#ifndef DCPU1_
#define DCPU1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Disable the CPU backend
*  @details This class is responsible for returning whether to disable CPU backend or not. */
class DCPU1 : public Helper
{
	public:
		/** Calculate variable DCPU1 from Intermediate Representation. Calculated variable DCPU1 is used for deciding whether to disable CPU backend.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

