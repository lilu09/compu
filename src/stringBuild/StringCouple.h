#ifndef STRINGCOUPLE
#define STRINGCOUPLE

#include <string>
#include <iostream>


class EntryComponent;
class Component;

/** @addtogroup group5

  @{
*/

/** @brief String Couple
*  @details This class contains a variable name and a value, it finds Helpers to calculate its value.
*/
class StringCouple
{
public:
	/** Constructor, intialize fields by parameter passed. */
	StringCouple(std::string k,std::string v);
	/** Calculate variable value by Intermediate Representation Component.*/
	void change(Component *com);
	/** Calculate variable value by Intermediate Representation EntryComponent.*/
	void change(EntryComponent *com);

	/** Variable name. */
	std::string key;
	/** Value of variable.*/
	std::string value;
	
	
};
/**	@} 
*/
#endif

