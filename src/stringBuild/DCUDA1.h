#ifndef DCUDA1_
#define DCUDA1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Disable the CUDA backend
*  @details This class is responsible for returning whether to disable CUDA backend or not. */
class DCUDA1 : public Helper
{
	public:
		/** Calculate variable DCUDA1 from Intermediate Representation. Calculated variable DCUDA1 is used for deciding whether to disable CUDA backend.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

