#ifndef ROSCD2_
#define ROSCD2_

#include <string>
#include <Helper.h>
#include <Component.h>


/** @addtogroup group5

  @{
*/

/** @brief Executable file name
*  @details This class is responsible for returning template type declaration, for example: template <typename T> where T is a generic type
*/
class ROSCD2 : public Helper
{
	public:
		/** Calculate variable TMTPST2 from Intermediate Representation. Calculated variable TMTPST2 is used for calculating template parameters.*/
		std::string getResult(Component*com);
};
/**	@} 
*/
#endif

