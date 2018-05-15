#ifndef XMLFILE_
#define XMLFILE_

#include <string>



/** @addtogroup group2
*
* @{
*/
/** @brief  Contain information for a single XML file*/

class XmlFile
{
public:
		/**  Default constructor, with nothing in it.*/
	XmlFile();
		/**  Constructor, initialize field by parameter.*/
	XmlFile(std::string fn);
		/**  This method print info of this class, used for verbose mode. */
	void show();
		/**  This field stores xml file name. */
	std::string filename;
};
/** @} */
#endif

