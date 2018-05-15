#ifndef CKN2_
#define CKN2_

#include <string>
#include <Helper.h>
#include <Node.h>

/** @addtogroup group5

  @{
*/

/** @brief cl_kernel structure name
*  @details This class is responsible for generating statement for cl_kernel structure(StarPU structure) name, for example: 'kernel_vector_scal' (assume vector_scal is interface name)
*/

class CKN2 : public Helper
{
	public:
		/** Calculate variable CKN2 from Syntax tree.Calculated variable CKN2 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
		/** Calculate variable CKN2 from Intermediate Representation. Calculated variable CKN2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};

/**	@} 
*/

#endif

