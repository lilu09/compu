#ifndef COMPONENTBASE_
#define COMPONENTBASE_

#include <string>

/** @addtogroup group2
*
* @{
*/

/** @brief Abstraction for Component and EntryComponent */
class ComponentBase
{
	public:
		/** if set to true, the first added implementation will become default implementation, which will be used for code generation*/
		bool defaultFlag;
};

/** @} */


#endif

