#ifndef SOPN2_
#define SOPN2_

#include <string>
#include <Helper.h>
#include <Node.h>

/** @addtogroup group5

  @{
*/

/** @brief Starpu opencl program name
*  @details This class is responsible for generating starpu opencl program(StarPU structure) name, for example: 'codelet_vector_scal' (assume vector_scal is interface name)
*/
class SOPN2 : public Helper
{
	public:
		/** Calculate variable SOPN2 from Syntax tree.Calculated variable SOPN2 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
		/** Calculate variable SOPN2 from Intermediate Representation. Calculated variable SOPN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

