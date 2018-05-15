#ifndef METHODLIST_
#define METHODLIST_

#include <Method.h>
#include <vector>

/** @addtogroup group2
*
* @{
*/
/** @brief  Intermediate Representation for all methods within an interface. */
class MethodList
{
public:
		/** Add a method to this container. */
	void add(Method *m);
		/**  Print info of Method list, used for verbose mode. */
	void printMe();
		/**  Return first method. */
	Method *getFirst();
private:
		/**  Container for methods. */
	std::vector<Method *> methods;
};
/** @} */
#endif

