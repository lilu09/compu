#ifndef STCFOMP2_
#define STCFOMP2_

#include <string>
#include <Helper.h>
#include <EntryComponent.h>


/** @addtogroup group5

  @{
*/

/** @brief Executable file name
*  @details This class is responsible for generating Executable file name, for example: 'vector_scal' (assume vector_scal is interface name)
*/
class STCFOMP2 : public Helper
{
	public:
		/** Calculate variable INSTCL from Intermediate Representation. Calculated variable INSTCL is used for replacement in template file.*/
		std::string getResult(EntryComponent* com);
};
/**	@} 
*/
#endif

