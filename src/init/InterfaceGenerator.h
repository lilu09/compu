#ifndef INTERFACE_GENERATOR_
#define INTERFACE_GENERATOR_


#include <vector>

#include <methods.h>


struct FileInf
{
	std::string infcName;
	std::string implName;
	std::vector<std::string> paramVec;
	std::string implFileName;
	std::string implType;
	std::string codeletName;
	std::string codeletFileName;
	std::string kernelName;
	std::string kernelHandleName;
	std::string queueName;
	std::string compilerName;
};

class InterfaceGenerator
{
	
public:
	
	InterfaceGenerator(const std::vector<std::string> &headerFilesList_);
	void generateXMLFiles();


private:
	FileInf fileInf;
	
	std::string paramList;
	std::string infcName;
	
	void generateImplFiles(std::string type);
	void generateImplFilesOcl(std::string type);
	
	void generateImplCodeFiles(std::string type);

	void generateInterfaceHeader(int index);
	void parseMethodString(std::string methodStr);
	
	const std::vector<std::string> &headerFilesList;
};


#endif

