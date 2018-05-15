#ifndef STCL2_
#define STCL2_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Cpu codelet core binding statement
*  @details This class is responsible for generating task creation loop if supported for an interface. 
*/
class STCL2 : public Helper
{
	public:
		/** Calculate variable STCL2 from Intermediate Representation. Calculated variable STCL2 is used for replacement in template file.*/
		std::string getResult(Component *com);
		
	private:
		void findParam(std::string accessMode, ParamList *paramList, Param *&p);
};
/**	@} 
*/
#endif

