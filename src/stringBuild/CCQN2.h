#ifndef CCQN2_
#define CCQN2_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief cl_command_queue structure name
*  @details This class is responsible for generating statement for cl_command_queue structure(StarPU structure) name, for example: 'queue_vector_scal' (assume vector_scal is interface name)
*/
class CCQN2 : public Helper
{
	public:
	    /** Calculate variable CCQN2 from Syntax tree.Calculated variable CCQN2 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
		/** Calculate variable CCQN2 from Intermediate Representation. Calculated variable CCQN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};

/**	@} 
*/

#endif

