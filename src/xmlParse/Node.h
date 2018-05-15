#ifndef NODE_
#define NODE_

#include <vector>
#include <string>
#include <error.h>

/** @addtogroup group1
*
* @{
*/
/** @brief Root for XML syntax tree */
class Node 
{
	
public:
	/** Constructor, initialize field tag.*/
	Node(std::string s);
	
	/** Constructor, initialize field tag and father. */
    Node(std::string s,Node *f);
    
	/** Add a child to this container. */
	void addchild(Node *node);
	
	/** Test if this node contains a child named 'key'.*/
	bool existChild(std::string key);
	
	/** Test if this node contains child or not.*/
	bool existChild();
	
	/** Get child by name.*/
	Node *getChild(std::string s);

	/** Tag of this node, for element type, this field denotes tag of XML element. */
	std::string tag;
	
	/** Father of this node.*/
	Node* father;
	
	/** Children of this node.*/
	std::vector<Node *> child;
	
	/** Print info of this node, used for verbose mode.*/
	virtual void print();
};

/** @} */
#endif

