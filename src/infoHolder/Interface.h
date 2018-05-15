#ifndef INTERFACE_
#define INTERFACE_

#include <Node.h>
#include <MethodList.h>
#include <XmlFileList.h>
/** @addtogroup group2
*
* @{
*/
/** @brief Intermediate Representation for a single interface. */
class Interface
{
public:
	
	/** Constructor, initialize fields by a syntax tree. This method is useful for building Intermediate Representation. */
	Interface(Node *aTree);
	
	/** Stub for Constructor. */
	void init();
	
	/** This function will scan all files from impPath(implementation directory), filter only xml files, and store those file names to xmls field, 
	so that further construction of component Intermediate Representation, such as implementations, can be built.*/
	void updateListImplXMLFiles();
	
	/** Print info of Interface, used for verbose mode. */
	void printMe();
	
	/** Boolean flag that will enable usage of history based performance models in StarPU for this component. */
	bool useHistoryModels;
	
	/** Boolean flag that will enable usage of regression based performance models in StarPU for all components. */
	bool useRegressionModels;
	
	/** Boolean flag that will enable usage of non-linear regression based performance models in StarPU for all components. */
	bool useNLRegressionModels;
	
	/** Boolean flag that can be used to disable generation of code for CUDA backend */
	bool disableCUDA;
	
	/** Boolean flag that can be used to disable generation of code for CPU backend */
	bool disableCPU;
	
	/** Boolean flag that can be used to disable generation of code for OpenCL backend */
	bool disableOpenCL;
	
	/**  Syntax tree passed from constructor, used by other member function to fetch info and update member variables. */
	Node *tree;
	
	/**  Interface name. */
	std::string name;
	
	/**  Path of Implementations which implement this interface . */
	std::string impPath;
	
	/**  Template (generic) types in the interface parameters. */
	std::vector<std::string> templateTypesVec;
	
	/**  Raw string containing template (generic) types in the interface parameters. e.g, "T,U" */
	std::string getRawTemplateTypesStr();
		
	/**  A list of methods this interface contains.*/
	MethodList *methods;
	
	/**  A list of xml files that annotates this interface's implementations.*/
	XmlFileList *xmlFiles; 
};
/** @} */
#endif

