
#include <Interface.h>
#include <Helper.h>
#include <EnvVar.h>
#include <helperFactory.h>
#include <Method.h>
#include <methods.h>
#include <algorithm>

using namespace std;

extern EnvVar env;

Interface::Interface(Node *aTree):tree(aTree),methods(new MethodList),xmlFiles(new XmlFileList())
{
	init();
}

// Used to initialize structure from XML (Node *)
void Interface::init()
{
	DEBUG_METHOD_ENTRY("init") // used for debugging purposes to trace problems...
	
	Helper *helper;
	//update name
	helper=helperFactory::createHelper("IN1");
	name="NF";
	if(helper)
	{
		name = helper->getResult(tree);
		delete helper;
	}
	
	//update path
	helper=helperFactory::createHelper("IMPA1");
	impPath="";
	if(helper)
	{
		impPath = helper->getResult(tree);
		delete helper;
	}
		
	if(impPath=="")
	{
		impPath="./"+name+"/";
	}
	
	helper=helperFactory::createHelper("TMTYPS1");
	string tmTypes="";
	if(helper)
	{
		tmTypes = helper->getResult(tree);
		delete helper;
	}
	
	string tmType="";
	
	while(tmTypes!="")
	{
		decode(tmTypes,tmType,',');
		tmType=trimSpaces(tmType);
		if(!tmType.empty())
			templateTypesVec.push_back(tmType);
			
		tmTypes=trimSpaces(tmTypes);	
	}
	
	helper=helperFactory::createHelper("UHBPM1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		useHistoryModels = (ret == "1") ? true : false;
		
		delete helper;
	}
	
	helper=helperFactory::createHelper("URBPM1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		useRegressionModels = (ret == "1") ? true : false;
		
		delete helper;
	}
	
	helper=helperFactory::createHelper("UNLRBPM1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		useNLRegressionModels = (ret == "1") ? true : false;
		
		delete helper;
	}
	
	if((useRegressionModels && useNLRegressionModels) || (useHistoryModels && useNLRegressionModels) || (useRegressionModels && useHistoryModels))
	{
		error("Multiple type of performance models options (useHistoryModels, useRegressionModels, useNLRegressionModels) set in XML file for interface: "+ name + ".");
	}
	
	helper=helperFactory::createHelper("DCPU1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		disableCPU = (ret == "1") ? true : false;
		
		delete helper;
	}
	
	helper=helperFactory::createHelper("DCUDA1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		disableCUDA = (ret == "1") ? true : false;
		
		delete helper;
	}
	helper=helperFactory::createHelper("DOPENCL1");
	if(helper)
	{
		string ret = helper->getResult(tree);
		disableOpenCL = (ret == "1") ? true : false;
		
		delete helper;
	}


	// create a single method, method name same as interface name and return type is void only.
	Method *m=new Method(name, "void", tree );
		
	//m->params->show();
	methods->add(m);

	//update xmlFiles
	updateListImplXMLFiles();
	
}

/**  Raw string containing template (generic) types in the interface parameters. e.g, "T,U" */
string Interface::getRawTemplateTypesStr()
{
	if(templateTypesVec.empty())
		return "";
		
	string ret=templateTypesVec[0];
	
	for(int i=1;i<templateTypesVec.size(); i++)
	{
		ret += "," + templateTypesVec[i];
	}
	return ret;
}

void Interface::updateListImplXMLFiles()
{
	DEBUG_METHOD_ENTRY("updateListImplXMLFiles") // used for debugging purposes to trace problems...
	
	//listing files
	vector<string> files;
	
    getFilesListFromDir(impPath,files);
	//filter non-xml files
	for (unsigned int i = 0;i < files.size();i++) 
	{
		//if it is a xml file, add to interface
		if(getSuffix(files[i],'.')=="xml")
		{
			if(std::find(env.disableXmlList.begin(), env.disableXmlList.end(), unCapitalizeString(files[i]))!=env.disableXmlList.end())
				continue;
			xmlFiles->add(new XmlFile(impPath+files[i]));
		}
	}
}

void Interface::printMe()
{
	cout<<endl<<"Interface name: "<<name<<endl;
	methods->printMe();
}

