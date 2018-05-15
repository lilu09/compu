#ifndef CODELETINFO_H
#define CODELETINFO_H

#include <string>
#include <Node.h>

/** @defgroup group2 Intermediate Representation
*
* @{
*/
/** @brief  OPENCL codelet information.*/
class CodeletInfo
{
public:
	
	/**  Default constructor, initialize every member variable to null. */
	CodeletInfo();
		
	/**  Constructor, every member variable is assigned by fetching correct info from XML syntax tree. This constructor is useful for conversion from XML parse tree to Intermediate Representation.*/
	CodeletInfo(Node *tree);
		
	/**  Stub for Constructor CodeletInfo(Node *tree). */
	void init(Node *tree);
		
	/**  Print info of this class. This method is useful for verbose mode.*/
	void printMe();

	
	/**  StarPU starpu_opencl_program structure name. More detail can be found on <A HREF="http://runtime.bordeaux.inria.fr/StarPU/">StarPU documentation</A>. This value is necessary for OPENCL wrapper on StarPU.*/
	std::string starpu_opencl_program;
		
	/**  StarPU cl_kernel structure name. More detail can be found on <A HREF="http://runtime.bordeaux.inria.fr/StarPU/">StarPU documentation</A>. This value is necessary for OPENCL wrapper on StarPU.*/
	std::string cl_kernel;
		
	/**  StarPU cl_command_queue structure name. More detail can be found on <A HREF="http://runtime.bordeaux.inria.fr/StarPU/">StarPU documentation</A>. This value is necessary for OPENCL wrapper on StarPU.*/
	std::string cl_command_queue;
		
	/**  Function name in OPENCL codelet file. This value is necessary for OPENCL wrapper on StarPU. */
	std::string kernel;
		
	/**  Codelet file name. This value is necessary for OPENCL wrapper on StarPU.*/
	std::string codelet_file;

};

/** @} */ 

#endif

