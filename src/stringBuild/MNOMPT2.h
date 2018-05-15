#ifndef MNOMPT2_
#define MNOMPT2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Used to initialize number of OpenMP threads, if OpenMP component
*  @details This class is responsible for generating the statement to initialize number of OpenMP threads, if OpenMP component, for example: 'omp_set_num_threads();' 
*/
class MNOMPT2 : public Helper
{
	public:
		/** Calculate variable MNOMPT2 from Intermediate Representation. Calculated variable INOMPT2 is used for replacement in template file.*/
		std::string getResult(Component *com);
};
/**	@} 
*/
#endif

