#ifndef IMD1_
#define IMD1_

#include <string>
#include <Helper.h>
#include <Node.h>


/** @addtogroup group5

  @{
*/

/** @brief Disable a certain implementation
*  @details This class is responsible for returning whether to disable a certain component implementation or not. */
class IMD1 : public Helper
{
	public:
		/** Calculate variable IMD1 from Intermediate Representation. Calculated variable IMD1 is used for deciding whether to disable a certain component implementation or not.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

