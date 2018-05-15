#ifndef IN1_
#define IN1_

#include <Helper.h>
#include <string>



/** @addtogroup group5

  @{
*/

/** @brief interface name
*  @details This class is responsible for generating interface name, for example: 'vector_scale' (assume vector_scal is interface name)
*/
class IN1 : public Helper
{
	public:
		/** extract interface name from syntax tree, which is from xml file that annotates an interface*/
		std::string getResult(Node *tree);
		/** Calculate variable IN1 from Intermediate Representation. Calculated variable IN1 is used for replacement in template file.*/
		std::string getResult(Component *com);

};
/**	@} 
*/
#endif

