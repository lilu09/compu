#ifndef RM2_
#define RM2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Multiple rules
*  @details This class is responsible for generating multiple rules, used in makefile generation, for example: 'vector_scal.o : vector_scal.c 
* @Tab g++ -I<starpu-install>/include -c $< @Ent vector_scal_cuda.o: vector_scal_cuda.cu 
* @Tab nvcc  -I<starpu-install>/include --compiler-options -fpermissive -c $<' (assume vector_scal is interface name)
*/
class RM2 : public Helper
{
	public:
		/** Calculate variable RM2 from Intermediate Representation. Calculated variable RM2 is used for replacement in template file.*/
		std::string getResult(EntryComponent *com);
};
/**	@} 
*/
#endif

