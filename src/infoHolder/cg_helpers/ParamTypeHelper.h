#ifndef PARAM_TYPE_HELPER_
#define PARAM_TYPE_HELPER_

#include <vector>
#include <string>
//#include <CG_ParamList.h>
#include <methods.h>
//#include <Node.h>

enum ParamTypeEnum { TYPE_VECTOR, TYPE_MATRIX, TYPE_VARIABLE_PTR, TYPE_OTHER, TYPE_CSR_MATRIX, TYPE_BCSR_MATRIX };

/** @addtogroup group2
*
* @{
*/
/** @brief  Helper for determining the parameter type whether it is some peppher type or not. */

class ParamTypeHelper
{
	public:
	/**!
	* A helper method that will determine whether the type given is a PEPPHER container type or an ordinary type
	* The logic is kept quite simple as a parameter type should be either a PEPPHER contaner type such as vector and matrix 
	* or a normal C/C++ data type including 1-D arrays.
	!*/
	static ParamTypeEnum checkParamType(std::string type)
	{
		type = trimSpaces(type); // remove leading and trailing spaces, if any
		type = capitalizeString(type); // capitalize to ensure that char-case does not matter.
				
		if(containString(type, "VECTOR"))
		  return TYPE_VECTOR;
		  
		if(containString(type,"MATRIX"))
		  return TYPE_MATRIX;  
		  
		if(containString(type,"VARIABLEPTR"))
			return TYPE_VARIABLE_PTR;
			  
		return TYPE_OTHER;
	};
	
	/**!
	* To get the element type, not relevant with new schema definition.
	*/
	static std::string getElementType(std::string type)
	{
		size_t found1 = type.find('<');
		if (found1 == std::string::npos)
		{
			error("Error while extracting element type from type: "+ type + ". Type should be specified e.g., Vector<int>");
		}
		
		size_t found2 = type.find('>');
		if (found2 == std::string::npos)
		{
			error("Error while extracting element type from type: "+ type + ". Type should be specified e.g., Vector<int>");
		}
		
		return type.substr(found1+1, found2-found1);
	};
};

/** @} */
#endif

