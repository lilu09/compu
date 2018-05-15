#ifndef ENVVAR
#define ENVVAR

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <InfContainer.h>

/** @brief Global structure, containing data used by all functions and classes. */
class EnvVar
{
public:
	/**  Entry Xml file name. The first xml file to be parsed. This info is passed from command line. */
	std::string entry;
	std::string ct_home;
	std::string static_constraint_eval_path;
	/**  Directory where SOFTWARE/data locates. This info is fetched from environmental variable of OS. */
	std::string path;
	/**  File that stores paths of XML syntax tree and their corresponding variable name. */
	std::string knowdlege_file;
	/**  File name of header part of wrapper template. */
	std::string wrapperHeaderTemplate;
	/**  File name of CPU function part of wrapper template. */
	std::string wrapperCpuTemplate;
	/**  File name of CUDA function part of wrapper template. */
	std::string wrapperCudaTemplate;
	/**  File name of OPENCL function part of wrapper template. */
	std::string wrapperOpenclTemplate;
	/**  File name of  wrapper function part of wrapper template. */
	std::string wrapperInfTemplate;
	/**  Header template file name. */
	std::string mainWrapperTemplate;
	/**  Makefile template file name. */
	std::string makefileTemplate;
	/** Extension for generated wrapper files, default : .h */
	std::string wrapperFilesExt;
	/**  XML Interface template file name. */
	std::string interfaceTemplate;

	/**  XML Implementation template file name. */
	std::string implTemplate;

	/**  XML Implementation template file name for OpenCL. */
	std::string implTemplateOcl;

		
	/**  XML schema file name, used by XML parser. */
	std::string schema;
	/**  std::string consists of name space and schema, required by XML parser. */
	std::string ns_schema;
	/**  Verbose mode level, from 1 to 3, which are more and more detailed. */
	int verboseLevel;
	/**  Act as a global variable. In some cases, it is useful for communication between functions. */
	std::string message;
	
	/** Boolean flag that will enable usage of history based performance models in StarPU for all components. */
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
	
	/** A STL vector that contains list of implementations that should not be used for code generation etc. */
	std::vector<std::string> disableImplList;
	
	
	/** A STL vector that contains list of iheader files from which an initial XML file should be generated */
	std::vector<std::string> headerFilesList;
	
	/** A STL vector that contains list of XML files that should not be considered. */
	std::vector<std::string> disableXmlList;
	
	/**  Container where file of field knowdlege_file is loaded at runtime. */
	std::map<std::string,std::string> kb;  //knowledge base
	
	/** @brief update path-related field, this method should only be called when path is set */
	void setInit();
	
};



#endif

