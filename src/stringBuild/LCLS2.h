#ifndef LCLS2_
#define LCLS2_

#include <string>
#include <Helper.h>
#include <Node.h>

/** @addtogroup group5

  @{
*/

/** @brief  Opencl codelet file name
*  @details This class is responsible for generating opencl codelet file name, for example: 'vector_scal_opencl_codelet.cl' (assume vector_scal is interface name)
*/
class LCLS2 : public Helper
{
	public:
		/** Calculate variable LCLS2 from Intermediate Representation. Calculated variable LCLS2 is used for replacement in template file.*/
		std::string getResult(Component *com);
		/** Calculate variable LCLS2 from Syntax tree.Calculated variable LCLS2 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

