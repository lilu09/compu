#ifndef ELEMENT_
#define ELEMENT_

#include <types.h>
#include <Node.h>

/** @defgroup group1 XML parsing
@{  */


/** @brief Element for XML syntax tree, subclass of Node */
class Element : public Node 
{
public:	
	/** Constructor, initialize field by parameters passed. */
	Element(std::string s);
	/** Content of XML Element. */
    std::string content;
	/** Attributes of XML Element.*/
	std::map <std::string, std::string> attrs;
	/** Add attribute to this container. */
	void addattr(std::string attr_name, std::string attr_value);
	/** Print info of this class, used for verbose mode.*/
	void print();
};

/**	@} 
*/

#endif

