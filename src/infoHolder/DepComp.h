#ifndef DEPITEM_
#define DEPITEM_

#include <vector>
#include <string>
#include <iostream>
#include <Component.h>


/** @addtogroup group2
*
* @{
*/
/** @brief  Dependent item, contains information about dependent component. */

class DepComp
{
public:
	/**  Default constructor, with nothing in it.*/
	DepComp();
	/**  Constructor, initialize member variables by interface name and xml file name.*/
	DepComp(std::string inf,std::string xml);
	/**  Print info of this class, used for verbose mode.*/
	void show();
	/**  Interface name.*/
	std::string infName;
	/**  XML file name.*/
	std::string xmlName;
	/**  Pointer to component specified by xml file(xmlName). */
	Component *com;
};

/** @} */
#endif

