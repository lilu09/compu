#ifndef XMLFILES_
#define XMLFILES_

#include <vector>
#include <XmlFile.h>


/** @addtogroup group2
*
* @{
*/
/** @brief  Container for XmlFile. */
class XmlFileList
{
public:
	/**  Add an Xml File to this container. */
	void add(XmlFile *x);
	/**  Print info of this class, used for verbose mode. */
	void show();
	/**  Get iterator at end. This method is useful for traversing this list and hide how container is implemented.*/
	std::vector<XmlFile *>::iterator getBegin();
	/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented.*/
	std::vector<XmlFile *>::iterator getEnd();
private:
	/**  Container for xml files. */
	std::vector<XmlFile *> xmlFiles;
};
/** @} */
#endif

