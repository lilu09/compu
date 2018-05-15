#ifndef COMPONENT_
#define COMPONENT_

#include <map>
#include <ComponentBase.h>
#include <Node.h>
#include <Interface.h>



class ComConfig;
class Implementation;
/** @addtogroup group2
*
* @{
*/
/** @brief  EntryComponent's dependent Components*/
class Component : public ComponentBase
{
	public:
	/**  Default constructor, with nothing in it.*/
	Component();
	/**  Constructor, initialize memeber variable by syntax tree. If deVar is set to TRUE, then first added implementation of same kind is set as default implementation. This method is useful for building Intermediate Representation. */
	Component(Node *tree, bool deVar);
	
	/**  Print name of Component and its implementations, used for verbose mode. */
	void printName(std::string delim);
	
	/**  Print name of implementations, used for verbose mode. */
	void printImps(std::string delim);
	
	/**  Print all necessary info of Component, used for verbose mode. */
	void printMe();
	
	/**  Generate a wrapper file, containing functions which intercept normal call and adapt it to StarPU platform.*/
	void generateWrapper();
	
	bool hasOpenMPImpl();

	void handle_constraints_pass();

	/**  Interface for the component. */
	Interface *intfc;
	
	/**  Configure for the component, store default implementations. */
	ComConfig *configure;
	
	/**  Store all implementations besides default implementations. */
	std::multimap<std::string, Implementation *> impls;
};

/** @} */
#endif

