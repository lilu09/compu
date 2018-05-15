
#include <EnvVar.h>

using namespace std;



void EnvVar::setInit()
{		
				knowdlege_file=path+"/knowledge/knowledge.cc";
				wrapperHeaderTemplate=path+"/template/wrapper_header_.cc";
				wrapperCpuTemplate=path+"/template/wrapper_cpu_.cc";
				wrapperCudaTemplate=path+"/template/wrapper_cuda_.cc";
				wrapperOpenclTemplate=path+"/template/wrapper_opencl_.cc";
				wrapperInfTemplate=path+"/template/wrapper_inf_.cc";
				mainWrapperTemplate=path+"/template/peppher_.h";
				interfaceTemplate=path+"/template/interface_xml_.cc";
				implTemplate=path+"/template/impl_xml_.cc";
				implTemplateOcl=path+"/template/impl_xml_opencl_.cc";
				schema=path+"/schema/ComponentMetaData.xsd";
				ns_schema="http://www.peppher.eu/ComponentMetaData0.1 "+schema;
				makefileTemplate=path+"/template/Makefile_.cc";
				useHistoryModels = false;
				verboseLevel = -1;
				disableOpenCL = disableCPU = disableCUDA = false;
				wrapperFilesExt = ".h";
	};
	





