
#include <iostream>
#include <Param.h>
#include <ParamList.h>
#include <methods.h>

using namespace std;

Param::Param(string name_, string type_, string elemType_, std::string partitionInf_, string acc, string num, std::string _csrNRows, 
			 std::string _csrRowOffsets, std::string _csrColIndices, std::string _csrFirst, bool _dummy) : name(trimSpaces(name_)), 
			 type(trimSpaces(type_)), elemType(trimSpaces(elemType_)), accessMode(capitalizeString(trimSpaces(acc))), 
			 numElements(trimSpaces(num)), metaDataList( new ParamList() ), metaTargetList( new ParamList() ), /*metaSourceLdParam (0),
			 metaTargetLdParam (0),*/ csrNRows(trimSpaces(_csrNRows)), csrRowOffsets(trimSpaces(_csrRowOffsets)), 
			 csrColIndices(trimSpaces(_csrColIndices)), csrFirst(trimSpaces(_csrFirst)), dummy(_dummy)
{
	if(name.empty() || type.empty())
		error("Type and/or name missing for a parameter. Each parameter must have a non-empty name and type");
		
	if(containString(type, "**")  || containString(type, "* *"))
		error("The type is unkown to the composition tool, "+ type);
		
	if(	isPeppherType()!=TYPE_OTHER && (elemType=="" || (containString(elemType, "*"))) )
		error("The PEPPHER container must have an element type which currently cannot be a pointer type! type: "+ type+", elemType: "+elemType);	
	isPointer = containString(type, "*");
	
	processPartition(partitionInf_);
	
	
	if(! (csrNRows.empty() || csrColIndices.empty() || csrRowOffsets.empty()))
	{
		pType = TYPE_CSR_MATRIX;
		return;
	}
	else if((!csrNRows.empty() || !csrColIndices.empty() || !csrRowOffsets.empty()))
		warn("Possible options missing in parameter: "+ name + ". A CSR parameter should specify csr_col_indices, csr_row_offsets and csr_nrows attributes.");
	
	pType = isPeppherType(); // what we get, ingorning CSR_type
}

Param::Param(Param *p): name(trimSpaces(p->name)), type(trimSpaces(p->type)), elemType(trimSpaces(p->elemType)), partInf(p->partInf), 
			accessMode(capitalizeString(trimSpaces(p->accessMode))), numElements(trimSpaces(p->numElements)), metaDataList(p->metaDataList),
			metaTargetList(p->metaTargetList), dimensions(p->dimensions), /*metaSourceLdParam (p->metaSourceLdParam), 
			metaTargetLdParam (p->metaTargetLdParam),*/ csrNRows(p->csrNRows), csrRowOffsets(p->csrRowOffsets), 
			csrColIndices(p->csrColIndices), csrFirst(p->csrFirst)
{
	if(containString(type, "**") || containString(type, "* *"))
		error("The type is unkown to the composition tool, "+ type);
		
	if(	isPeppherType()!=TYPE_OTHER && (elemType=="" || (containString(elemType, "**") || containString(elemType, "* *"))))
		error("The PEPPHER container must have an element type which currently cannot be a pointer type! type: "+ type+", elemType: "+elemType);
	
	isPointer = containString(type, "*");
	
	if(! (csrNRows.empty() || csrColIndices.empty() || csrRowOffsets.empty()))
	{
		pType = TYPE_CSR_MATRIX;
		return;
	}
	else if((!csrNRows.empty() || !csrColIndices.empty() || !csrRowOffsets.empty()))
		warn("Possible options missing in parameter: "+ name + ". A CSR parameter should specify csr_col_indices, csr_row_offsets and csr_nrows attributes.");
	
	pType = isPeppherType(); // what we get, ingorning CSR_type
}

/** To decide whether parameter can be partitioned */
bool Param::partitionParam()
{
	return ( dimensions>0 && partInf.dimensions>0 );
}



void Param::setMetaType(std::string name, MetaParamTypes type)
{
	metaTypeMap.insert(std::make_pair(name, type));
}

void Param::processPartition(string partitionInf_)
{
	DEBUG_METHOD_ENTRY("processPartition") // used for debugging purposes to trace problems...
	
	partInf.rawString = partitionInf_;
	
	partitionInf_ = trimSpaces(partitionInf_);
	
	if(partitionInf_=="") // no partitiong for this parameter
	{
		partInf.dimensions=0;
		return;
	}
	if(containString(partitionInf_,",")) // assume 2D partitioning
	{
		partInf.dimensions = 2; // can be a recursive method or a loop but as dim<=2 so its simpler for now.
		
		string part;
		decode(partitionInf_,part,',');
		part=trimSpaces(part);
		
		int dim=0;
		
		if(part == "")
		{
		   warn("partition left empty, parameter: " + name + ", partition should be either *(none), ?(tunable) or a size expression. Will consider it no partitioning (*)!");
		   part = "*";
		}
		
		
		else if(from_string<int>(dim, part, std::dec))
		{
			if(dim<=1)
				part = "*";
		}
		
		if(part == "*")
		{
			--partInf.dimensions;
		    partInf.partTypeD1 = NO_PARTITION;
		}
		 
		else if (part == "?")
		{
			warn("partition factor is not specified, left tunable (?) which is not supported yet! Will ignore it: "+ name+".");
			--partInf.dimensions;
			partInf.partTypeD1 = TUNABLE_PARTITION;
		}
		else // assume it should be a fixed partition size
		{
			partInf.partTypeD1 = FIXED_PARTITION;
			partInf.sizeD1 = part;
		}
		
		decode(partitionInf_,part,',');
		part=trimSpaces(part);
		
		if(part == "")
		{
//		   warn("partition left empty, parameter: " + name + ", partition should be either *(none), ?(tunable) or a size expression. Will consider it no partitioning (*)!");
		   part = "*";
		}
		else if(from_string<int>(dim, part, std::dec))
		{
			if(dim<=1)
				part = "*";
		}
		 
		if(part == "*")
		{
			--partInf.dimensions;
		    partInf.partTypeD2 = NO_PARTITION;
		}
		   
		else if (part == "?")
		{
			warn("partition factor is not specified, left tunable (?) which is not supported yet! Will ignore it: "+ name+".");
			--partInf.dimensions;
			partInf.partTypeD1 = TUNABLE_PARTITION;
		}
		else // assume it should be a fixed partition size
		{
			partInf.partTypeD2 = FIXED_PARTITION;
			partInf.sizeD2 = part;
		}
	}
	else 
	{
		partInf.dimensions = 1;
		
		string part;
		decode(partitionInf_,part,',');
		part=trimSpaces(part);
		
		if(part == "")
		{
		   warn("partition left empty, parameter: " + name + ", partition should be either *(none), ?(tunable) or a size expression. Will consider it no partitioning (*)!");
		   part == "*";
		}
		
		if(part == "*")
		{
			--partInf.dimensions;
		    partInf.partTypeD1 = NO_PARTITION;
		}
		   
		else if (part == "?")
		{
			warn("partition factor is not specified, left tunable (?) which is not supported yet! Will ignore it: "+ name+".");
			--partInf.dimensions;
			partInf.partTypeD1 = TUNABLE_PARTITION;
		}
		else // assume it should be a fixed partition size
		{
			partInf.partTypeD1 = FIXED_PARTITION;
			partInf.sizeD1 = part;
		}
	}
}

//Param::Param(Param_internal *p):name(p->name),type(p->type),accessMode(p->accessMode),numElements(p->numElements)
//{
//	
//}

void Param::printMe()
{
	cout<<"  parameter name: "+name<<", type: "+type<<", accessMode: "+accessMode<<"."<<endl;
}

void Param::show(string space)
{
	cout<<space+"Name: "<<name<<endl;
	cout<<space+"type: "<<type<<endl;
	cout<<space+"isPointer: "<< (isPointer? "true": "false" ) <<endl;
	cout<<space+"Access Mode: "<<accessMode<<endl;
	cout<<space+"Number of Elements: "<<numElements<<endl;
	cout<<space+"Meta list: ";
	
	vector<Param*>::iterator it;
	for(it=metaDataList->getBegin();it!=metaDataList->getEnd();++it)
	{
		(*it)->showName();
	}

	cout<<endl<<space+"Target list: ";
	
	for(it=metaTargetList->getBegin();it!=metaTargetList->getEnd();++it)
	{
		(*it)->showName();
	}
	cout<<endl<<endl;
}

/** return whether this operand type is a scalar type */
bool Param::isScalar()
{
	return ((isPeppherType()==TYPE_OTHER) && (dimensions==0));
}

/** return whether this operand type is a PEPPHER type */
ParamTypeEnum Param::isPeppherType()
{
	return ParamTypeHelper::checkParamType(type);
}


string Param::getElementType()
{
	return elemType; // ParamTypeHelper::getElementType(type);
}

void Param::showName()
{
	cout<<name<<" ";
}


bool Param::getMetaType(std::string name, MetaParamTypes type)
{
	std::multimap<std::string, MetaParamTypes>::iterator it;
	for (it= metaTypeMap.equal_range(name).first; it!=metaTypeMap.equal_range(name).second; ++it)
	{
		if((*it).second == type)
			return true;
	}
	return false;
}

void Param::removeMetaType(std::string name, MetaParamTypes type)
{
	std::multimap<std::string, MetaParamTypes>::iterator it;
	for (it= metaTypeMap.equal_range(name).first; it!=metaTypeMap.equal_range(name).second; ++it)
	{
		if((*it).second == type)
			metaTypeMap.erase(it);
	}
}


void Param::removeMetaType(std::string name)
{
	metaTypeMap.erase(name);
}

/** Method used to calculate the "dimension" variable of the parameter, called by ParameterList after creating all parameters. */
void Param::calculateDimensions()
{
	DEBUG_METHOD_ENTRY("calculateDimensions") // used for debugging purposes to trace problems...
	
	// by default assume scalar value
	this->dimensions=0;
	
	if(pType == TYPE_CSR_MATRIX) // CSR sparse matrices should be stored in a vector ...
		this->dimensions=1; 
		
	else if(pType == TYPE_OTHER) // if it is not a peppher container
	{
		if( metaDataList->cg_paramList->size()==1 ) // vector
		   this->dimensions=1; 
		   
		else if( metaDataList->cg_paramList->size()==2 ) // matrix
		   this->dimensions=2; 
	}
	else if(pType == TYPE_VECTOR) // if it is a peppher Vector 
		this->dimensions=1; 
		
	else if (pType == TYPE_MATRIX) // if it is a peppher Matrix
		this->dimensions=2; 
}

