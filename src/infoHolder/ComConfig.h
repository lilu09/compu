#ifndef COMCONFIG_
#define COMCONFIG_

#include <string>
#include <map>
#include <Implementation.h>

/** @addtogroup group2
*
* @{
*/

/** @brief  Component configuration, specifying default implementations for CPU, CUDA, and OPENCL platform*/
class ComConfig
{
public:
	/** Default constructor. This constructor set all default implementations to null. */
	ComConfig();
	/** Set default implementation. This method is useful not only for building Intermediate Representation, but also for writing passes which can affect code generation result. */
	void set(std::string type,Implementation *imp);

	/**  Get default implementation. This method is useful for code generation since only default implementation which has been set is used for code generation. */
	Implementation *get(std::string type);
	/**  Test if default implementation of certain type is set or not. This method is useful for code generation since only default implementation which has set is used for code generation. */
	bool exist(std::string type);
	
	/**  Print info of this class. This method is useful for verbose mode. */
	void printMe();
private:
	/**  Member variable config, container for default implementation. Map structure is used so that reset erase previous settings.*/
	std::map<std::string, Implementation *> config;
};

/** @} */
#endif

