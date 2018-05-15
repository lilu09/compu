#ifndef PGBCL2_
#define PGBCL2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Parameter gap bridgement.
*  @details This class is responsible for generating parameter gap bridgement, that is, extract data from StarPU data handles, for example: '(float *)STARPU_VECTOR_GET_PTR((struct starpu_vector_interface *)buffers[0])' (assume vector_scal is interface name)
*/
class PGBCL2 : public Helper
{
	public:
		/** Calculate variable PGBCL2 from Intermediate Representation. Calculated variable PGBCL2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

