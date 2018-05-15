
#include <iostream>
#include <Method.h>

using namespace std;


void findParam(std::string accessMode, ParamList *paramList, Param *&p)
{
	DEBUG_METHOD_ENTRY("findParam") // used for debugging purposes to trace problems...
	
	vector<Param *>::iterator it;
	
	// first try to find a right parameter with partitioning
	for(it=paramList->getBegin();it!=paramList->getEnd();++it)
	{
		if ( (*it)->accessMode==accessMode && (*it)->partitionParam() )
		{
			p = *it;
			break;
		}
	}
}


void Method::setPartitioningParam()
{
	DEBUG_METHOD_ENTRY("setPartitioningParam") // used for debugging purposes to trace problems...
	
	if(supportPartitioning)
	{
		ParamList *paramList =	params;

		Param *param = 0;
		
		findParam("WRITE", paramList, param);
		if(!param)
		{
			findParam("READWRITE", paramList, param);
		}	
		if(!param)
		{
			findParam("READ", paramList, param);
		}
		if(!param)
		{
			error("Could not find a parameter with partitioning support in interface: " + name + ".");
		}
		
		if(param->partInf.dimensions==1)
		{
			if(param->dimensions==1)
				paramXPart = param;
			else if(param->dimensions==2)	 // if the parameter is a matrix (2D9 but partition is 1D
			{
				if(param->partInf.partTypeD1 == FIXED_PARTITION) // partition horizontally
					paramXPart = param;
				else                       // partition vertically
					paramYPart = param;	
			}
		}
		else if(param->partInf.dimensions==2)
		{
			
			paramXPart = param;
			paramYPart = param;
		}
		else
			error("Number of dimensions currently supported are at most 2."); 	
	}
}

Method::Method(std::string name_, std::string returnType_, Node *tree_): name(name_), returnType(returnType_), paramXPart(0), paramYPart (0)
{
	DEBUG_METHOD_ENTRY("Method") // used for debugging purposes to trace problems...
	
	params = new ParamList(tree_, this);
	
	supportPartitioning = false;
	
	vector<Param *>::iterator it;
	
	for(it=params->getBegin();it!=params->getEnd();++it)
	{
		if ( (*it)->partInf.dimensions>0 )
		{
			// ensure that partitioning is not specified for "any" scalar parameter
			if((*it)->isScalar())
			   error("Partitioning can be specified only for array(1D,2D) parameters and not for scalar parameter: " + (*it)->name + ".");
			
			if ( (*it)->partInf.partTypeD1 == TUNABLE_PARTITION || (*it)->partInf.partTypeD2 == TUNABLE_PARTITION )   
			{
				warn("Tunable partitioning type is not supported yet! Will revert to normal un-partitioned execution, parameter: " +  (*it)->name);
				supportPartitioning = false;
				break;
			}
			else
				supportPartitioning = true;
		}
	}
	
	setPartitioningParam();
}

void Method::printMe()
{
	DEBUG_METHOD_ENTRY("printMe") // used for debugging purposes to trace problems...
	
	//print signiture
	cout<<"signiture: "<<getSignature()<<endl;
	//print parameter attributes
	cout<<"Parameter Attributes: "<<endl;
	vector<Param *>::iterator it;
	for(it=params->getBegin();it!=params->getEnd();++it)
	{
		(*it)->printMe();
	}
}

string Method::getSignature()
{
	DEBUG_METHOD_ENTRY("getSignature") // used for debugging purposes to trace problems...
	
	string sig=returnType;
	sig+=" "+name+"(";
	vector<Param *>::iterator it;
	for(it=params->getBegin();it!=params->getEnd();++it)
	{
		sig+=(*it)->type+" "+(*it)->name;
		if(it!=params->getEnd()-1)
			sig+=",";
	}
	return sig+")";
}

