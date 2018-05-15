#ifndef MAO2_
#define MAO2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Multiple rules
*  @details This class is responsible for generating the output name for makefile initial target e.g. all : <outputname>
*/
class MAO2 : public Helper
{
	public:
		/** Calculate variable MAO2 from Intermediate Representation. Calculated variable RM2 is used for replacement in template file.*/
		std::string getResult(EntryComponent *com);
};
/**	@} 
*/
#endif

