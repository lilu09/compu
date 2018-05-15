#ifndef CAP_
#define CAP_

#include <string>
#include <Helper.h>

/** @addtogroup group5

  @{
*/
/** @brief String Capitalization.
*  
*/
class Cap : public Helper
{
	public:
	    /** Covert std::string to Capitalized form, used in std::string calculation. */
		std::string getResult(std::string value);
};

/**	@} 
*/
#endif

