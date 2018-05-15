#ifndef INWQM2_
#define INWQM2_

#include <string>
#include <Helper.h>
#include <EntryComponent.h>


/** @addtogroup group5

  @{
*/

/** @brief Executable file name
*  @details This class is responsible for generating Executable file name, for example: 'vector_scal' (assume vector_scal is interface name)
*/
class INWQM2 : public Helper
{
	public:
		/** Calculate variable INWQM2 from Intermediate Representation. Calculated variable INWQM2 is used for replacement in template file.*/
		std::string getResult(EntryComponent*com);
};
/**	@} 
*/
#endif

