#include <InterfaceGenerator.h>
#include <MakeDir.h>
#include <EnvVar.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <deque>


using namespace std;

extern EnvVar env;


InterfaceGenerator::InterfaceGenerator(const std::vector<string> &headerFilesList_): headerFilesList(headerFilesList_)
{
	
}


bool startsWith(string str, string prefix)
{
   if (!str.compare(0, prefix.size(), prefix))
      return true;
      
   return false;
}


void removeEmptyLineFromStart(std::string filename)
{
  deque <string> lines;
  std::string s;
	
  // load the file
  ifstream inf( filename.c_str() );  // You must supply the proper filename
  if (!inf)
  {
  	std::cerr<<"Unable to open file: "<<filename<<"\n";
  	return;
  }        
  
  while (getline( inf, s ))
  {
    lines.push_back( s );
  }
    
  inf.close();
  
  for (deque<string>::iterator line= lines.begin(); line != lines.end(); ++line)
  {
  	*line = trimSpaces(*line);
  	while(*line == "")
  	{
  		line = lines.erase(line);
  		if(line != lines.end())
  			*line = trimSpaces(*line);
		else
			break;
  	}
  	if(line == lines.end())
  		break;
  }
	
  // rewrite the new text to file
  ofstream outf( filename.c_str() );
  if (!outf)
  {
  	std::cerr<<"Unable to open file: "<<filename<<"\n";
  	return;
  } 
  for (deque<string>::iterator line= lines.begin(); line != lines.end(); ++line)
  {
    outf << *line << '\n';
  }
  outf.close();
	
}


void InterfaceGenerator::generateImplCodeFiles(std::string type)
{
	type = capitalizeString(trimSpaces(type));
	string lowType = unCapitalizeString(type);
	
    ofstream os;
#ifndef _WIN32	
	string fileName = fileInf.infcName + "/" + fileInf.implFileName;
	if(lowType=="opencl")
	{   
		string name= fileInf.infcName + "/" + fileInf.codeletFileName;
		ofstream os_cl(name.c_str());
		if ( os_cl.is_open() )
			os_cl.close();
	}
#else
	string fileName = fileInf.implFileName;
	if(lowType=="opencl")
	{   
		string name= fileInf.codeletFileName;
		ofstream os_cl(name.c_str());
		if ( os_cl.is_open() )
			os_cl.close();
	}
#endif
    os.open(fileName.c_str());
   

   if ( os.is_open() )
   {
   	 if (lowType == "opencl")
   	 {
   	 	os<<"#include <starpu.h>\n";
		os<<"#include <starpu_opencl.h>\n\n";
		os<<"extern struct starpu_opencl_program "<<fileInf.codeletName <<";\n";
		os<<"extern cl_kernel "<< fileInf.kernelHandleName <<";\n";
		os<<"extern cl_command_queue "<<fileInf.queueName<<";\n\n";
   	 }
	  os<<"void "<<fileInf.implName<<" (";
	  if(!fileInf.paramVec.empty())
	  {
	  	os<<fileInf.paramVec[0];
	  	for(int i=1;i<fileInf.paramVec.size();i++)
	  	{
	  		os<<", "<<fileInf.paramVec[i];
	  	}
	  }
	  os<<")\n{\n\t\n}\n";
   }
   else
   {
   	error("Error while opening file: "+ fileName + "\n");
   }
 
  os.close();
	
}


void InterfaceGenerator::generateImplFiles(std::string type)
{
	type = capitalizeString(trimSpaces(type));
	string lowType = unCapitalizeString(type);
	
	fileInf.infcName = infcName;
	fileInf.implName = infcName+"_"+lowType;
	fileInf.implFileName = infcName+"_"+lowType+".c" + ((type=="CUDA")? "u": "pp");
	fileInf.compilerName = ((type=="CUDA")? "nvcc": "g++");
	fileInf.implType = type;
	
	map<string, string> pool;
	pool.insert(std::make_pair("INFNAME", fileInf.infcName));
	pool.insert(std::make_pair("IMPNAME", fileInf.implName));
	pool.insert(std::make_pair("FILENAME", fileInf.implFileName));
	pool.insert(std::make_pair("COMPILERNAME", fileInf.compilerName));
	pool.insert(std::make_pair("IMPTYPE", fileInf.implType ));

#ifndef _WIN32	
	string file = infcName + "/" + infcName+"_"+lowType+".xml";
#else
	string file = infcName+"_"+lowType+".xml";
#endif	
	replaceWithVariablesValue(env.implTemplate,file,&pool);	
	
	removeEmptyLineFromStart(file);
	
}



void InterfaceGenerator::generateImplFilesOcl(std::string type)
{
	type = capitalizeString(trimSpaces(type));
	string lowType = unCapitalizeString(type);
	
	
	fileInf.infcName = infcName;
	fileInf.implName = infcName+"_"+lowType;
	fileInf.implFileName = infcName+"_"+lowType+".c" + ((type=="CUDA")? "u": "pp");
	fileInf.codeletName = "cl_codelet_" + infcName;
	fileInf.kernelHandleName = "cl_kernel_" + infcName;
	fileInf.kernelName = "kernel_" + infcName;
	fileInf.queueName = "cl_queue_" + infcName;
	fileInf.codeletFileName = infcName+"_"+lowType + "_codelet.cl";
	fileInf.compilerName = "g++";
	fileInf.implType = type;
	
//	std::cerr<< "fileInf.codeletName: "<<fileInf.codeletName<<",  fileInf.kernelHandleName: "<< fileInf.kernelHandleName<<"fileInf.queueName: "<<fileInf.queueName<<", fileInf.codeletFileName: "<<fileInf.codeletFileName<<"   ***\n";
	
	map<string, string> pool;
	pool.insert(std::make_pair("INFNAME", fileInf.infcName));
	pool.insert(std::make_pair("IMPNAME", fileInf.implName));
	pool.insert(std::make_pair("FILENAME", fileInf.implFileName));
	pool.insert(std::make_pair("CLNAME", fileInf.codeletName));
	pool.insert(std::make_pair("KRHNAME", fileInf.kernelHandleName));
	pool.insert(std::make_pair("KRNAME", fileInf.kernelName));
	pool.insert(std::make_pair("QUNAME", fileInf.queueName));
	pool.insert(std::make_pair("CLFILENAME", fileInf.codeletFileName));
	
//	pool.insert(std::make_pair("IMPTYPE", type));

#ifndef _WIN32	
	string file = infcName + "/" + infcName+"_"+lowType+".xml";
#else
	string file = infcName+"_"+lowType+".xml";
#endif	
	replaceWithVariablesValue(env.implTemplateOcl,file,&pool);	
	
	removeEmptyLineFromStart(file);
	
}

void InterfaceGenerator::parseMethodString(string methodStr)
{
	istringstream iss(methodStr);
	string retType="";
	if(iss.good() && iss.peek()==13)
		iss.ignore();
	iss>>retType;
	
	string lowType = unCapitalizeString(trimSpaces(retType));
	
	if(lowType != "void")
	{
		std::cout<<"*** Unknown return type: "<<retType<<". Currently, the peppher interface supports only void data type. Will ignore it and will assume void data type.\n";
	}
	
	
	// Check for method name
	if(!iss.good())
	{
		error("The method declaration looks erroneous! Should be of form <retType> <methodName> ( <paramType> <paramName>, more params comma separated... );\n");
	}	
	string methodName, rawStr, rem="";
	iss>>rawStr;
	if(containString(rawStr, "("))
	{
		rem = getSuffix(rawStr, '('); // save string after ( in remaining;
		removeSuffix(rawStr, '(');
	}
	methodName = rawStr;
	
	methodName = trimSpaces(methodName);
	if(methodName=="")
	{
		error("The method declaration looks erroneous! Should be of form <retType> <methodName> ( <paramType> <paramName>, more params comma separated... );\n");
	}
	
	infcName = methodName;
	
	// Check for params
	if(!iss.good())
	{
		error("The method declaration looks erroneous! Should be of form <retType> <methodName> ( <paramType> <paramName>, more params comma separated... );\n");
	}
//	char test[256];
	string params="";
	getline(iss, params); //test,256,')');		
	removeSuffix(params, ')');
	
	params = rem + " " + params;
	
	params = trimSpaces(params);
	
	while(params[0]=='(')
	{
		params = trimSpaces(params.substr(1));
	}

	
	
	while(params!="")
	{
		string single;
		decode(params, single, ',');
		single = trimSpaces(single);
		
		string type, pName;
		decode(single, type, ' ');
		pName = single;
		
		type = trimSpaces(type);
		pName = trimSpaces(pName);
		if(containString(type, " "))
		{
			error("The method declaration looks erroneous! Should be of form <retType> <methodName> ( <paramType> <paramName>, more params comma separated... );\n");
		}
		if(containString(pName, " "))
		{
			error("The method declaration looks erroneous! Should be of form <retType> <methodName> ( <paramType> <paramName>, more params comma separated... );\n");
		}
		
		if(startsWith(pName,"**"))
		{
			pName = pName.substr(2);
			type += " **";
		}
		if(pName[0]=='*')
		{
			pName = pName.substr(1);
			type += " *";
		}
		
		fileInf.paramVec.push_back(type + " " + pName);
		
		paramList += "<peppher:parameter name=\"" + pName + "\" type=\"" + type + "\" accessMode=\"\" />\n";
	}

}

void InterfaceGenerator::generateInterfaceHeader(int index)
{
	ifstream infile(headerFilesList[index].c_str());
		
	if(!infile.is_open())
		error("Cannot open the header file: " + headerFilesList[index]);
	
	string line;
	string methodStr="";
	while(infile.good())
	{
		getline(infile,line);
		line = trimSpaces(line);
		
		string prefix = "#";
		if(line=="" || line[0]=='#')
			continue;
		
		if(startsWith(line,"template"))
		 	continue;
		
		if(containString(line,"{")) // in-case it is a method definition
		{
			removeSuffix(line, '{');
		  	methodStr += " " + line;
		  	break;
		}
		// else assume it is a method declaration that should end with a ;	
		else if(containString(line,";"))
		{
			removeSuffix(line, ';');
		  	methodStr += " " + line;
		  	break;
		}
		else
			methodStr += " " + line;
	}	
	if(methodStr=="")
		error("Could not find a suitable method declaration! A method declaration should start on a new line, can space one or more lines and should end with a semicolon (;)");
	else
	{
		methodStr = trimSpaces(methodStr);
		std::cout<<"Following is a (possible) method declaration found to start the component-template-files generation process: \n\n"<<methodStr<<"\n\n";	
	}

	parseMethodString(methodStr);
	
	map<string, string> pool;
	pool.insert(std::make_pair("INFNAME", infcName));
	pool.insert(std::make_pair("PARAMLIST", paramList));
	
	replaceWithVariablesValue(env.interfaceTemplate,infcName+".xml",&pool);	
	
	removeEmptyLineFromStart(infcName+".xml");
	
	#ifndef _WIN32
	
	string path = "./"+infcName;
	if (mkpath(path.c_str(), 0777) != 0)
	{
		error("Unable to create the directory: "+ path);
	}
          
    #endif
    generateImplFiles("CPU");
    generateImplCodeFiles("CPU");
	generateImplFiles("CUDA");
	generateImplCodeFiles("CUDA");
	generateImplFilesOcl("OPENCL");
	generateImplCodeFiles("OPENCL");
	std::cout<<"Finished!\n";
}




void InterfaceGenerator::generateXMLFiles()
{
	for(int i=0;i<headerFilesList.size(); i++)
	{
		generateInterfaceHeader(i);
	}
}

