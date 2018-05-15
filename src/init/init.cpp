#include <cstdlib>
#include <fstream>
#include <init.h>
#include <error.h>
#include <methods.h>
#include <InterfaceGenerator.h>


using namespace std;

void usage()
{
//	 [-useHistoryModels] [-v1|v2|v3]
	cout<<"The composition tool is a prototype, developed as part of the PEPPHER project.\n";
	cout<<"It can be used to generate StarPU code for the PEPPHER components by processing\n";
	cout<<"meta-data specified in XML files. Morevoer, it can perform basic static composition\n";
	cout<<" decisions (e.g. enabling/disabling a certain backend or component implementation).\n"; 
	
	cout<<"\nUsage:\n";
	cout<<"\nTwo modes:\n";
	cout<<"\n  1st mode: Generation of XML and C-source files from a C/C++ header file. Utility mode!\n";
	cout  <<"            Can be used when writing components in a quick way.\n";
	cout<<"\n\tcompose -generateCompFiles=\"xxx\"\n";
	cout<<"\n\t-generateCompFiles=\"xxx\" - Header file(s)(comma-separated, if multiple) \n";
	cout<<"                            containing a single C/C++ method declaration.\n";
	cout<<"\n  2nd mode: Code generation mode\n";
	cout<<"\n\tcompose <XML file> [options]\n";
	
	cout<<"\nOptions**:\n\n";
	cout<<"\t-v=xxx                   - Verbose mode [1 | 2 | 3 | 0*]\n";
	cout<<"\t-wrapperFilesExt=\"xxx\"   - Specify generated wrapper files extension (Default: \".h\") \n";
	cout<<"\t-useHistoryModels        - To enable usage of StarPU history performance models \n";
	cout<<"\t                           for all components.\n";
	cout<<"\t-useRegressionModels     - To enable usage of StarPU regression performance models \n";
	cout<<"\t                           for all components.\n";
	cout<<"\t-useNLRegressionModels   - To enable usage of StarPU non-linear regression performance\n";
	cout<<"\t                           models for all components.\n";
	cout<<"\t-disableXMLFiles=\"xxx\"   - List of implementation XML file-names(comma-separated)\n";
	cout<<"\t                           that should not be processed.\n";
	cout<<"\t-disableImpls=\"xxx\"      - Name of implementations(comma-separated) that should \n";
	cout<<"\t                           not be used for generating code. Still processes XML \n";
	cout<<"\t                           files but dont generate code.\n";
	cout<<"\t-disableCPU              - To disable CPU implementations for all components.\n";
	cout<<"\t-disableCUDA             - To disable CUDA implementations for all components.\n";
	cout<<"\t-disableOpenCL           - To disable OpenCL implementations for all components.\n";
	
	cout<<"\n\t*  = Default if not provided explicitly.";
	cout<<"\n\t** = Options names are case-insensitive.\n\n";
	
//	cout<<endl<<"[ ] marks optional parameters."<<endl;
//	cout<<"-useHistoryModels Will enable usage of history based performance models with all components."<<endl;
//	cout<<"-v<no> Verbose Mode level <no>"<<endl<<endl;
//	
//	cout<<endl<<"usage: compose <MainXMLFile.xml> [-useHistoryModels] [-v1|v2|v3]"<<endl;
//	cout<<endl<<"[ ] marks optional parameters."<<endl;
//	cout<<"-useHistoryModels Will enable usage of history based performance models with all components."<<endl;
//	cout<<"-v<no> Verbose Mode level <no>"<<endl<<endl;
	exit(0);
}

void paramCheck(int num)
{
	if(num<2)
		usage();
}

void getEnv(string name, string &varS)
{
	char *var = getenv(name.c_str());
	if(!var)
	{
		string message="Environment variable "+name+" is not set";
		fatal(message);
	}
	varS=var;
}

void setEnvPath(EnvVar *env)
{
	string var;

	string name="CT_HOME";
	getEnv(name, var);
	env->ct_home= var;
	env->static_constraint_eval_path= var+"/src/static_constraint_eval";
	env->path= var + "/data";
	
}


void setVerbose(EnvVar *env, string value)
{
	if(value=="1")
		env->verboseLevel=1;
	else if(value=="2")
		env->verboseLevel=2;
	else if(value=="3")
		env->verboseLevel=3;
	else if(value!="0")
		usage();
}

void parseEnvVar(EnvVar *env, int argC,char **argV)
{
	
	for(int i=1;i < argC; i++)
	{
		string arg = unCapitalizeString(argV[i]);	
		
		if (containString(arg,"-generatecompfiles"))
		{
			arg = argV[i];	
			
			string multi;
			string single;
			
			multi = getSuffix(arg,'=');
			
			while(multi!="")
			{
				decode(multi,single,',');
				single=trimSpaces(single);
				if(single!="")
				{
					env->headerFilesList.push_back(single);
				}
			}
			
			if(!env->headerFilesList.empty())
			{
				std::cout<<"\n*** Utility mode: will only generate header files. see compose --help\n\n";
				return;
			}
			else
			{
//				std::cout<<"\n*** Utility mode: will only generate header files. see compose --help\n\n";
				std::cout<<"\n*** No file name(s) given for header file(s) that can be used to generate header files. See compose --help.\n\n";
				// Will discard this option and will resume the normal code generation processing.
				exit(0);
			}
			
		}
	}
	
	for(int i=1;i < argC; i++)
	{
		string arg = unCapitalizeString(argV[i]);	
		if (containString(arg,"-generatecompfiles")) // do nothing in this mode
		{  }
		else if (containString(arg,"-disablexmlfiles"))
		{
			string multi;
			string single;
			
			multi = getSuffix(arg,'=');
			
			while(multi!="")
			{
				decode(multi,single,',');
				single=trimSpaces(single);
				if(single!="")
				{
					string sfx = getSuffix(single,'.');
					
					if(sfx == "")
					{
						removeSuffix(single,'.');
						single += ".xml";
					}
						
					else if(sfx!="xml")	
					{
					    error("Unknown type of XML files found in -disablexmlfiles with name: " + single + "! Should either have .xml extension or write just file name in which case .xml will be appended");
					}
					
					env->disableXmlList.push_back(single);
				}
			}
		}
		
		else if(getSuffix(arg, '.')=="xml")
		{
			env->entry=argV[i];
			ifstream is;
			is.open(argV[i]);
			if(!is.is_open())
			{
				arg = argV[i];
				error("Unable to open the XML file specified: "+ arg  + ". Please specify a valid XML file name.");
			}
			is.close();
		}
		
		else if(arg=="--help")
			usage();
		
		else if (arg == "-usehistorymodels")
			env->useHistoryModels = true;
		
		else if (arg == "-useregressionmodels")
			env->useRegressionModels = true;	
		
		else if (arg == "-usenlregressionmodels")
			env->useNLRegressionModels = true;		
		
		else if (containString(arg,"-disableimpls"))
		{
			string multi;
			string single;
			
			multi = getSuffix(arg,'=');
			
			while(multi!="")
			{
				decode(multi,single,',');
				single=trimSpaces(single);
				if(single!="")
				{
					env->disableImplList.push_back(single);
				}
			}
		}
		
		else if (containString(arg,"-wrapperfilesext"))
		{
			string multi;
			string single;
			
			multi = trimSpaces(getSuffix(arg,'='));
			
			if(multi!="")
			{
				decode(multi,single,',');
				single = trimSpaces(single);
				if(single!="")
					env->wrapperFilesExt = (single[0]=='.')? single : ("." + single);
			}
		}
				
		else if (arg == "-disablecpu")
			env->disableCPU = true;		
				
		else if (arg == "-disablecuda")
			env->disableCUDA = true;	
		
		else if (arg == "-disableopencl")
			env->disableOpenCL = true;		
			
		else if(containString(arg,"-v="))
		{
			string single;
			
			single = trimSpaces(getSuffix(arg,'='));
			
			setVerbose(env, single);	
		}
		else
			std::cout<<"*** Unknown option "<<argV[i]<<" passed as command line argument. Will ignore it! See compose --help\n";
	}
	if(env->entry=="")
	{
		error("No XML file found to start the parsing process. Please specify a valid XML file name with extension .xml. See compose --help");
	}
	
	if((env->useRegressionModels && env->useNLRegressionModels) || (env->useHistoryModels && env->useNLRegressionModels) || (env->useRegressionModels && env->useHistoryModels))
	{
		error("Only one type of performance models options (useHistoryModels, useRegressionModels, useNLRegressionModels) can be set. See compose --help");
	}
}



void printFile(string file)
{
	DEBUG_METHOD_ENTRY("printFile") // used for debugging purposes to trace problems...
	
	ifstream is;
	string line;
	is.open(file.c_str());
	if ( is.is_open() )
	{
		while(is.good())
	    {
		  getline(is,line);
		  cout<<line<<endl;
	    }
    }
    else
	{
	    cout << "Error opening file: "<<file<<"\n";
	}
}


void initPrintInfo(EnvVar *env)
{
	DEBUG_METHOD_ENTRY("initPrintInfo") // used for debugging purposes to trace problems...
	
	if(env->verboseLevel>=1)
	{
		cout<<endl<<"/************************************************************************/"<<endl;
		cout<<"Translation Initializtion Infomation: "<<endl;
		cout<<"Environmental variable CT_HOME: "<<env->path<<endl;
		cout<<"XML Entry File: "<<env->entry<<endl;
		cout<<"Verbose Level: "<<env->verboseLevel<<endl;
		cout<<"/************************************************************************/"<<endl<<endl;
	}
}

void sysInit(EnvVar *env, int argC, char **argV)
{
	DEBUG_METHOD_ENTRY("sysInit") // used for debugging purposes to trace problems...
	
	paramCheck(argC); // check the paramteres given are according to usage scenario.
	setEnvPath(env); // sets EnvVar->path = CT_HOME
	env->setInit(); // Calls EnvVar->setInit which internally updates all file paths w.r.t to path set above using setEnvPath.
	parseEnvVar(env, argC,argV);
	
	if(!env->headerFilesList.empty())
	{
		InterfaceGenerator infcGen(env->headerFilesList);
		infcGen.generateXMLFiles();
		exit(0);
	}
	
	loadKeyValFileToMap(env->knowdlege_file,&env->kb); // loads the knowledge.cc file which contains ampping between variables and XML paths
	initPrintInfo(env); // prints certain information if verbose mode is 1 or higher.
}

