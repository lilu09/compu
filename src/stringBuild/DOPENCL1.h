#ifndef DOPENCL1_
#define DOPENCL1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Disable the OPENCL backend
*  @details This class is responsible for returning whether to disable OPENCL backend or not. */
class DOPENCL1 : public Helper
{
	public:
		/** Calculate variable DOPENCL1 from Intermediate Representation. Calculated variable DOPENCL1 is used for deciding whether to disable OPENCL backend.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

