#ifndef DepCompList_
#define DepCompList_

#include <vector>
#include <string>
#include <iostream>
#include <DepComp.h>


using namespace std;

/** @addtogroup group2
*
* @{
*/

/** @brief  Container for DepComp. */
class DepCompList
{
public:
	/**  Add one DepComp. */
	void add(DepComp *p);
	/**  Get iterator at beginning. This method is useful for traversing this list and hide how list is implemented. */
   std::vector<DepComp *>::iterator getBegin();
	/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented.*/
   std::vector<DepComp *>::iterator getEnd();

private:
	/**  Container for DepComps. */
	std::vector<DepComp *> list;
};


/** @} */
#endif

