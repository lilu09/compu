#ifndef HELPER_
#define HELPER_

#include <map>
#include <string>
#include <sstream>
#include <Node.h>
#include <Component.h>
#include <EntryComponent.h>
#include <error.h>
#include <vector>
#include <Constraints.h>
#include <iostream>


/** @addtogroup group5

  @{
*/

/** @brief Abstraction for all std::string calculation classes
*  @details There are two main methods, one for conversion from syntax tree to string, 
*  and one for conversion from Intermediate Representation to string.
*/

class Helper
{
public:
	/** Abstraction for functions that extract info from syntax tree, used for Intermediate Representation construction.*/
	virtual std::string getResult(Node *tree){ return "DefaultValue";}
	/** Abstraction for functions that extract info from intermediate representation, used for header and wrapper generation.*/
	virtual std::string getResult(Component *com) { return "DefaultValue";}
        /** abstraction for functions that extract info from intermediate representation, used for makefile generation.*/
	virtual std::string getResult(EntryComponent *com){ return "DefaultValue";}
	/** abstraction for functions that transform one std::string to another, used by other Helper.*/
	virtual std::string getResult(std::string value){ return "DefaultValue";}
	virtual Constraints get_result(Node *tree) { return Constraints(); }
	virtual Constraints get_result(Component *com) { return Constraints(); }
	
};
/**	@} 
*/
#endif

