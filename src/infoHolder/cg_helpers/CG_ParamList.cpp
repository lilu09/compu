#include <CG_ParamList.h>
#include <Element.h>
#include <error.h>
#include <helperFactory.h>

#include <Method.h>


using namespace std;

CG_ParamList::CG_ParamList()
{
	DEBUG_METHOD_ENTRY("CG_ParamList") // used for debugging purposes to trace problems...
	
	initMember();
}

CG_ParamList::CG_ParamList(Node *aTree, Method *method_):tree(aTree), method(method_)
{
	DEBUG_METHOD_ENTRY("CG_ParamList") // used for debugging purposes to trace problems...
	
	initMember();
	initFromNode();
//	showAllList();
}




void CG_ParamList::add(Param *p)
{
	DEBUG_METHOD_ENTRY("add") // used for debugging purposes to trace problems...
		
	(*list).push_back(p);
}

void CG_ParamList::add(vector<Param*> *p,Param* curr)
{
	DEBUG_METHOD_ENTRY("add") // used for debugging purposes to trace problems...
		
	(*p).push_back(curr);
}

void CG_ParamList::initMember()
{
	DEBUG_METHOD_ENTRY("initMember") // used for debugging purposes to trace problems...
		
	list=new vector<Param*>;
	raw=new vector<Param*>;  
	//independent variables
	indep=new vector<Param*>;
	paramReadOnly=new vector<Param*>;
	paramDataHandle=new vector<Param*>;
}

void CG_ParamList::initFromNode()
{
	DEBUG_METHOD_ENTRY("initFromNode") // used for debugging purposes to trace problems...
	
	Node *target;
	locate(tree,env.kb["PARAM1"],target);
	updateValue(target);
	updateMeta(target);
	
	// To calculate dimensions of each parameter, called after relationship between parameters have been established
	int size = raw->size();
	for(int i=0;i<size;++i)
	{
		(*raw)[i]->calculateDimensions();
	}
	
	updateMetaLdParam(target);
	
	updateCSRMeta();
	
	/* The following code check for recursive relationships that is possible in case of sparse matrices where a meta
	* data parameter can itself contain other parameter as its meta-data. For example, colIndices can contain nrows as its meta-data
	* while colIndices itself is metadata for actual sparse matrices. So the following code break this relationship.
	*/
	for(int i=0;i<size;++i)
	{
		if( (int)(*raw)[i]->metaTargetList->cg_paramList->size()!=0)
		{
			std::vector<Param*>::iterator iter = (*raw)[i]->metaTargetList->cg_paramList->list->begin();
		    while (iter != (*raw)[i]->metaTargetList->cg_paramList->list->end())
		    {
		        if ((*iter)->metaTargetList->cg_paramList->size()!=0)
		        {
		        	(*raw)[i]->removeMetaType((*iter)->name);
		        	(*iter)->metaDataList->cg_paramList->list->clear(); // clear the list as it is
		            iter = (*raw)[i]->metaTargetList->cg_paramList->list->erase(iter);
		        }
		        else
		        {
		           ++iter;
		        }
		    }
		}
	}
	
	updateIndep();
	classify();	
}

/** given the root node of parameters in a syntax tree,  this function will extract every parameter under that node,
and puch them into parameter list  within this class, that is "raw2" field*/
void CG_ParamList::updateValue(Node *target)
{
	DEBUG_METHOD_ENTRY("updateValue") // used for debugging purposes to trace problems...
	
	int size=target->child.size();
	string name, type, elemType, accessMode, numElements, meta_data, meta_type, partInf;
	string csrNRows, csrColIndices, csrRowOffsets, csrFirst;
	Param *curr;

	for(int i=0;i<size;++i)
	{
			 name=trimSpaces( ( (Element *)target->child[i] )->attrs["name"] );
			 type=trimSpaces( ((Element *)target->child[i])->attrs["type"] );
			 elemType=trimSpaces( ((Element *)target->child[i])->attrs["elemType"] );
			 partInf=trimSpaces( ((Element *)target->child[i])->attrs["partition"] );
			 accessMode=trimSpaces( ((Element *)target->child[i])->attrs["accessMode"] );
			 numElements=trimSpaces( ((Element *)target->child[i])->attrs["numElements"] );
			 
			 csrNRows=trimSpaces( ( (Element *)target->child[i] )->attrs["csr_nrows"] );
			 csrColIndices=trimSpaces( ( (Element *)target->child[i] )->attrs["csr_col_indices"] );
			 csrRowOffsets=trimSpaces( ( (Element *)target->child[i] )->attrs["csr_row_offsets"] );
			 csrFirst=trimSpaces( ( (Element *)target->child[i] )->attrs["csr_first"] );
			 curr=new Param(name, type, elemType, partInf, accessMode, numElements, csrNRows, csrRowOffsets, csrColIndices, csrFirst);
			 add(raw,curr);
	}

}


void CG_ParamList::updateMeta(Node *target)
{
	DEBUG_METHOD_ENTRY("updateMeta") // used for debugging purposes to trace problems...
	
	int size;
	string meta,curr_name;
	size=target->child.size();
	
	string metas,meta2;
	
	Param *tmpPArray[3];
	for(int i=0;i<size;++i)
	{
		metas=((Element *)target->child[i])->attrs["numElements"];
		curr_name=((Element *)target->child[i])->attrs["name"];
		curr_name=trimSpaces(curr_name);
		
		for(int i=0; i<3;i++)
		{
			tmpPArray[i] = 0;
		}

		int num=0;
		while(metas!="")
		{
			decode(metas,meta2,',');
			meta2=trimSpaces(meta2);
			
			if(meta2.empty())
				continue;
			
				
			if(lookupByName(raw,meta2, false))
			{
				tmpPArray[num] = lookupByName(raw,meta2);
				
//				lookupByName(raw,curr_name)->metaDataList->addCG(lookupByName(raw,meta2));
//				
//				lookupByName(raw,meta2)->setMetaType(curr_name, SIZE_PARAM);
//				
//				lookupByName(raw,meta2)->metaTargetList->addCG( lookupByName(raw,curr_name) );
			}
			else
			{
				// Add a dummy param just to hold that information
				Param *curr = new Param(meta2, "int", "", "", "read", "", "", "", "", "", true);
				tmpPArray[num] = curr;
				
//				curr->setMetaType(curr_name, SIZE_PARAM);
//				lookupByName(raw,curr_name)->metaDataList->addCG(curr);
			}	
			num++;
		}
		
		if(lookupByName(raw,curr_name, false) && num>0)
		{			 
			 if(num == 1)
			 {
				 lookupByName(raw,curr_name)->metaDataList->addCG(tmpPArray[0]);
				 
				 if(lookupByName(raw,curr_name)->pType == TYPE_CSR_MATRIX)
				 	tmpPArray[0]->setMetaType(curr_name, CSR_SIZE_PARAM);
				 else	
				 	tmpPArray[0]->setMetaType(curr_name, SIZE_PARAM);
				 	
				 tmpPArray[0]->metaTargetList->addCG( lookupByName(raw,curr_name) );
			 }
			 else if(num == 2)
			 {
				 lookupByName(raw,curr_name)->metaDataList->addCG(tmpPArray[0]);
				 tmpPArray[0]->setMetaType(curr_name, MATRIX_NROWS_PARAM);
				 tmpPArray[0]->metaTargetList->addCG( lookupByName(raw,curr_name) );
				 
				 lookupByName(raw,curr_name)->metaDataList->addCG(tmpPArray[1]);
				 tmpPArray[1]->setMetaType(curr_name, MATRIX_NCOLS_PARAM);
				 tmpPArray[1]->metaTargetList->addCG( lookupByName(raw,curr_name) );
			 }
			 else
			 	error("Three dimensional are not supported yet. \n");
		}
	}
}




void CG_ParamList::updateCSRMeta()
{
	DEBUG_METHOD_ENTRY("updateCSRMeta") // used for debugging purposes to trace problems...
	
	
	int size;
	string name, csrFirst, csrNRows, csrColIndices, csrRowOffsets;
	
	size = raw->size();
	for(int i=0;i<size;++i)
	{
		if( (*raw)[i]->pType == TYPE_CSR_MATRIX)
		{
			name=(*raw)[i]->name;
			
			if(!((*raw)[i]->csrFirst.empty()))
			{
				csrFirst = (*raw)[i]->csrFirst;
				if(lookupByName(raw,csrFirst, false))
				{
					lookupByName(raw,name)->metaDataList->addCG(lookupByName(raw,csrFirst));
					
					lookupByName(raw,csrFirst)->setMetaType(name, CSR_FIRST_PARAM);
					
					lookupByName(raw,csrFirst)->metaTargetList->addCG( lookupByName(raw,name) );
				}
				else
				{
					// Add a dummy param just to hold that information
					Param *curr = new Param(csrFirst, "int", "", "", "read", "", "", "", "", "", true);
					curr->setMetaType(name, CSR_FIRST_PARAM);
					lookupByName(raw,name)->metaDataList->addCG(curr);
				}
			}
			
			
			if(!((*raw)[i]->csrColIndices.empty()))
			{
				csrColIndices = (*raw)[i]->csrColIndices;
				if(lookupByName(raw,csrColIndices, false))
				{
					lookupByName(raw,name)->metaDataList->addCG(lookupByName(raw,csrColIndices));
					
					lookupByName(raw,csrColIndices)->setMetaType(name, CSR_COL_INDICES_PARAM);
					
					lookupByName(raw,csrColIndices)->metaTargetList->addCG( lookupByName(raw,name) );
				}
				else
				{
					// Add a dummy param just to hold that information
					Param *curr = new Param(csrColIndices, "int", "", "", "read", "", "", "", "", "", true);
					curr->setMetaType(name, CSR_COL_INDICES_PARAM);
					lookupByName(raw,name)->metaDataList->addCG(curr);
				}
			}
			
			if(!((*raw)[i]->csrRowOffsets.empty()))
			{
				csrRowOffsets = (*raw)[i]->csrRowOffsets;
				if(lookupByName(raw,csrRowOffsets, false))
				{
					lookupByName(raw,name)->metaDataList->addCG(lookupByName(raw,csrRowOffsets));
					
					lookupByName(raw,csrRowOffsets)->setMetaType(name, CSR_ROW_OFFSETS_PARAM);
					
					lookupByName(raw,csrRowOffsets)->metaTargetList->addCG( lookupByName(raw,name) );
				}
				else
				{
					// Add a dummy param just to hold that information
					Param *curr = new Param(csrRowOffsets, "int", "", "", "read", "", "", "", "", "", true);
					curr->setMetaType(name, CSR_ROW_OFFSETS_PARAM);
					lookupByName(raw,name)->metaDataList->addCG(curr);
				}
			}
			
			if(!((*raw)[i]->csrNRows.empty()))
			{
				csrNRows = (*raw)[i]->csrNRows;
				if(lookupByName(raw,csrNRows, false))
				{
					lookupByName(raw,name)->metaDataList->addCG(lookupByName(raw,csrNRows));
					
					lookupByName(raw,csrNRows)->setMetaType(name, CSR_NROWS_PARAM);
					
					lookupByName(raw,csrNRows)->metaTargetList->addCG( lookupByName(raw,name) );
				}
				else
				{
					// Add a dummy param just to hold that information
					Param *curr = new Param(csrNRows, "int", "", "", "read", "", "", "", "", "", true);
					curr->setMetaType(name, CSR_NROWS_PARAM);
					lookupByName(raw,name)->metaDataList->addCG(curr);
				}
			}
		}
	}
}

void CG_ParamList::updateMetaLdParam(Node *target)
{
	DEBUG_METHOD_ENTRY("updateMetaLdParam") // used for debugging purposes to trace problems...
	
	int size;
	string meta,curr_name;
	size=target->child.size();
	Param *tmpP = 0;
	
	string metas,meta2;
	for(int i=0;i<size;++i)
	{
		metas=((Element *)target->child[i])->attrs["descRowWidth"];
		
		if(metas!="")
		{
			curr_name=((Element *)target->child[i])->attrs["name"];
			curr_name=trimSpaces(curr_name);
			decode(metas,meta2,',');
			meta2=trimSpaces(meta2);
			
			if(lookupByName(raw,meta2, false))
			{
				lookupByName(raw,curr_name)->metaDataList->addCG(lookupByName(raw,meta2));
				
				lookupByName(raw,meta2)->setMetaType(curr_name, MATRIX_LD_PARAM);
				
				lookupByName(raw,meta2)->metaTargetList->addCG( lookupByName(raw,curr_name) );
			}
			else
			{
				// Add a dummy param just to hold that information
				Param *curr = new Param(meta2, "int", "", "", "read", "", "", "", "", "", true);
				curr->setMetaType(curr_name, MATRIX_LD_PARAM);
				lookupByName(raw,curr_name)->metaDataList->addCG(curr);
			}	
		}
	}
}

/* Independent parameter means all parameters except those who decribe size or load(width) of others. This info is useful for StarPU because only Independent variable should be transfered by StarPU.*/
void CG_ParamList::updateIndep()
{
	DEBUG_METHOD_ENTRY("updateIndep") // used for debugging purposes to trace problems...
	
	int size;
	
	size = raw->size();
	for(int i=0;i<size;++i)
	{
		if( (int)(*raw)[i]->metaTargetList->cg_paramList->size()==0)
			add(indep,(*raw)[i] );
	}
}

void CG_ParamList::classify()
{
	DEBUG_METHOD_ENTRY("classify") // used for debugging purposes to trace problems...
	
	int size;
	
	size=indep->size();
	for(int i=0;i<size;++i)
	{
		if( (*indep)[i]->accessMode=="READ" && (*indep)[i]->isScalar() && ((*indep)[i]->isPointer == false)) // only if it is passed as read only and is a scalar value and not a pointer.
			add(paramReadOnly,(*indep)[i] );
		else
			add(paramDataHandle,(*indep)[i] );
	}
}


Param *CG_ParamList::lookupByName(vector<Param*> *curr,string name_, bool throwError)
{
	DEBUG_METHOD_ENTRY("lookupByName") // used for debugging purposes to trace problems...
	
	int size=curr->size();
	name_=trimSpaces(name_);
	for(int i=0;i<size;++i)
	{
		   if( (*curr)[i]->name==name_ ) 
		   	  return  (*curr)[i];
	}
	if(throwError)
		error("Cannot find the parameter with name: " + name_ + ". Spell wrong?");
	else
		warn("Cannot find the parameter with name: " + name_ + ". Spell wrong?");
	return 0;
}


int CG_ParamList::size()
{
	DEBUG_METHOD_ENTRY("size") // used for debugging purposes to trace problems...
	
	return list->size();
}


/**  Calculate parameters passed for readOnly struct args to the starpu task, e.g., float factor; */
string CG_ParamList::getROPD1()
{
	DEBUG_METHOD_ENTRY("getROPD1") // used for debugging purposes to trace problems...
	
	int size=paramReadOnly->size();
	string result=" ";
	for(int i=0;i<size;++i)
	{
		result += (*paramReadOnly)[i]->type+" "+(*paramReadOnly)[i]->name+";";
	}
	return result;
}

/** Calculate interface parameter list based on original paramters, e.g. vector_scal(float *arr, int size, float factor) */
string CG_ParamList::getIPL1()
{
	DEBUG_METHOD_ENTRY("getIPL1") // used for debugging purposes to trace problems...
	
	int size=raw->size();
	string result=" ";
	if(size>0)
	{		
		for(int i=0;i<size;++i)
		{
			if(i!=0)
				result += ", ";
				
			if((*raw)[i]->isPeppherType() == TYPE_OTHER) // if a peppher container then dont create the starpu_data_handle_t
				result += (*raw)[i]->type+" "+(*raw)[i]->name;
			else
				result += (*raw)[i]->type+"<"+ (*raw)[i]->getElementType() +"> &"+(*raw)[i]->name;
		}
	}
	return result;
}


/** Calculate parameters passed for readOnly struct args to the starpu task, e.g., arg.factor = factor */
string CG_ParamList::getROAA2(std::string infName)
{
	DEBUG_METHOD_ENTRY("getROAA2") // used for debugging purposes to trace problems...
		
	int size=paramReadOnly->size();
	string result=" ", name_;
	for(int i=0;i<size;++i)
	{
		name_=(*paramReadOnly)[i]->name;
		if(isAsynchronousCall())
			result += "arg_"+infName+"->"+name_+"="+name_+";";
		else
			result += "arg_"+infName+"."+name_+"="+name_+";";	
	}

	return result;
}


/** Calculate number of all parameters that will be passed as data handle to the StarPU, used for setting, e.g. task->nbuffers = 1 */
string CG_ParamList::getIWVN2()
{
	DEBUG_METHOD_ENTRY("getIWVN2") // used for debugging purposes to trace problems...
	
	int size=paramDataHandle->size();
	stringstream iss;
	iss<<size;
	return iss.str();
}


/** Calculate starpu data handle name for all parameters that will be passed as data handle to the StarPU, e.g. starpu_data_handle_t arr_handle; */
string CG_ParamList::getHD2()
{
	DEBUG_METHOD_ENTRY("getHD2") // used for debugging purposes to trace problems...
	
	int size=paramDataHandle->size();
	string result=" ";
	for(int i=0;i<size;++i)
	{
		if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if a peppher container then dont need this
		{
			result += "starpu_data_handle_t " + (*paramDataHandle)[i]->name + "_handle;";
			
			if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning then create starpu_data_filter structure
			{
				if( (*paramDataHandle)[i]->pType==TYPE_CSR_MATRIX ) // sparse matrices
				{
					string varName = (*paramDataHandle)[i]->name + "_filter_handle";
				 	result += "\nstruct starpu_data_filter " +  varName + ";\n";			 	
				 	result += "memset(&" + varName + ", 0, sizeof(" + varName + "));\n";
				    result += varName + ".filter_func = starpu_vertical_block_filter_func_csr;\n";
				    
				    string meta_ = "NF";
				    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, CSR_SIZE_PARAM))
				    {
				    	meta_ = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, CSR_SIZE_PARAM)->name;
				    }
				    else
				    	warn("Could not find a suitable meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
				    
				    result += varName + ".nchildren = (" + meta_ + "/ (" + (*paramDataHandle)[i]->partInf.sizeD1 + "));\n";
				}
				else if( (*paramDataHandle)[i]->dimensions==1 ) // vector
				{
				 	string varName = (*paramDataHandle)[i]->name + "_filter_handle";
				 	result += "\nstruct starpu_data_filter " +  varName + ";\n";			 	
				 	result += "memset(&" + varName + ", 0, sizeof(" + varName + "));\n";
				    result += varName + ".filter_func = starpu_block_filter_func_vector;\n";
				    
				    string meta_ = "NF";
				    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, SIZE_PARAM))
				    {
				    	meta_ = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, SIZE_PARAM)->name;
				    }
				    else
				    	warn("Could not find a suitable meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
				    	
//				    string meta_ = (* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[0]->name;
				    result += varName + ".nchildren = (" + meta_ + "/ (" + (*paramDataHandle)[i]->partInf.sizeD1 + "));\n";
				 } 
				else if( (*paramDataHandle)[i]->dimensions==2 ) // matrix
				{
					string varNameX = (*paramDataHandle)[i]->name + "_horiz_filter_handle";
					string varNameY = (*paramDataHandle)[i]->name + "_vert_filter_handle";
					string rows, columns;
					
					if((*paramDataHandle)[i]->partInf.partTypeD1==FIXED_PARTITION)
					{
						result += "\nstruct starpu_data_filter " +  varNameX + ";\n";
						result += "memset(&" + varNameX + ", 0, sizeof(" + varNameX + "));\n";
						result += varNameX + ".filter_func = starpu_vertical_block_filter_func;\n";
						rows = "NF";
					    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NROWS_PARAM))
					    {
					    	rows = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NROWS_PARAM)->name;
					    }
					    else
					    	warn("Could not find a suitable row meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
//						rows=(* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[0]->name;
						result += varNameX + ".nchildren = (" + rows + "/ (" + (*paramDataHandle)[i]->partInf.sizeD1 + "));\n";
					}
				 	if((*paramDataHandle)[i]->partInf.partTypeD2==FIXED_PARTITION)
				 	{
				 		result += "\nstruct starpu_data_filter " +  varNameY + ";\n";			 	
				 		result += "memset(&" + varNameY + ", 0, sizeof(" + varNameY + "));\n";
				 		result += varNameY + ".filter_func = starpu_block_filter_func;\n";
				 		columns = "NF";
					    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NCOLS_PARAM))
					    {
					    	columns = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NCOLS_PARAM)->name;
					    }
					    else
					    	warn("Could not find a suitable column meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
//						columns=(* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[1]->name;
					    result += varNameY + ".nchildren = (" + columns + "/ (" + (*paramDataHandle)[i]->partInf.sizeD2 + "));\n";
				 	}    
				}
			}
		}
	}
	return result;
}


/** Calculate starpu data handle registration string e.g. starpu_vector_data_register(....);  */
string CG_ParamList::getDRS2()
{
	DEBUG_METHOD_ENTRY("getDRS2") // used for debugging purposes to trace problems...
	
	 string result=" ";
	 int size=paramDataHandle->size();
	 string name_, meta_;
	 for(int i=0;i<size;++i)
	 {
	 	if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // only create these statements if it is not a peppher container
		{
			 name_=(*paramDataHandle)[i]->name;
			 
			 if( (*paramDataHandle)[i]->pType==TYPE_CSR_MATRIX ) // sparse matrices
			 {
			 	meta_ = "NF";
			 	if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, CSR_SIZE_PARAM))
			    	meta_ = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, CSR_SIZE_PARAM)->name;
			    else
			    	warn("Could not find a suitable meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
			    	
//			 	meta_=(* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[0]->name;
			 	result += "starpu_csr_data_register(&" + name_ + "_handle,0, " + meta_ + "," +(*paramDataHandle)[i]->csrNRows + ", (uintptr_t)" + name_ + ", (uint32_t *)" + (*paramDataHandle)[i]->csrColIndices + ", (uint32_t *)" + (*paramDataHandle)[i]->csrRowOffsets + "," + ((*paramDataHandle)[i]->csrFirst.empty()? "0": (*paramDataHandle)[i]->csrFirst) + ", sizeof(" + name_+"[0]));\n";
				
				if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning
					result += "starpu_data_partition(" + name_ + "_handle, &" + name_ +"_filter_handle);\n";
			 }
			 else if ((*paramDataHandle)[i]->isScalar()) // if it is simple variable operand in StarPU
			 {
				result += "starpu_variable_data_register(  &" + name_ + "_handle, 0, (uintptr_t)" + ( ((*paramDataHandle)[i]->isPointer) ? "": "&") + name_ + ", sizeof("+ (((*paramDataHandle)[i]->isPointer)  ? "*": "") + name_ + " ));\n";
			 }
			 else if( (*paramDataHandle)[i]->dimensions==1 ) // vector
			 {
		 		meta_ = "NF";
			    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, SIZE_PARAM))
			    {
			    	meta_ = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, SIZE_PARAM)->name;
			    }
			    else
			    	warn("Could not find a suitable meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");

				result += "starpu_vector_data_register(  &"+ name_ +"_handle, 0, (uintptr_t)" + name_ + ", "+meta_+", sizeof("+name_+"[0] ));\n";
				
				if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning
					result += "starpu_data_partition(" + name_ + "_handle, &" + name_ +"_filter_handle);\n";
			 } 
			else if( (*paramDataHandle)[i]->dimensions==2 ) // matrix
			{
				string rows = "NF", columns = "NF";
				
			    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NROWS_PARAM))
			    	rows = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NROWS_PARAM)->name;
			    else
			    	warn("Could not find a suitable row meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
			    	
			    if((*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NCOLS_PARAM))
			    	columns = (*paramDataHandle)[i]->metaDataList->getMetaType((*paramDataHandle)[i]->name, MATRIX_NCOLS_PARAM)->name;
			    else
			    	warn("Could not find a suitable row meta-data size parameter for parameter: "+ (*paramDataHandle)[i]->name + ". Generated code will possibly be erroneous.\n ");
			    	
//				rows=(* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[0]->name;
//				columns=(* (*paramDataHandle)[i]->metaDataList->cg_paramList->list)[1]->name;
				result += "starpu_matrix_data_register(  &" + name_ + "_handle, 0, (uintptr_t)" + name_ + ", "+columns+","+columns+","+rows+", sizeof("+name_+"[0] ));\n";
				
				if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning
				{
					if((*paramDataHandle)[i]->partInf.partTypeD1==FIXED_PARTITION && (*paramDataHandle)[i]->partInf.partTypeD2==FIXED_PARTITION)
						result += "starpu_data_map_filters(" + name_ + "_handle, 2, &" + name_ +"_horiz_filter_handle,  &" + name_ +"_vert_filter_handle);\n";
					else if((*paramDataHandle)[i]->partInf.partTypeD1==FIXED_PARTITION)
						result += "starpu_data_partition(" + name_ + "_handle, &" + name_ +"_horiz_filter_handle);\n";
					else if((*paramDataHandle)[i]->partInf.partTypeD2==FIXED_PARTITION)
						result += "starpu_data_partition(" + name_ + "_handle, &" + name_ +"_vert_filter_handle);\n";	
				}
			}
			else // maybe 3-dimensional or more! not supported yet
			{
				(*paramDataHandle)[i]->show("  ");
			    error("Unknown operand dimensions detected for preceding parameter.\n");
			}
		}
		else if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning for peppher containers
		{
			if((*paramDataHandle)[i]->isPeppherType() == TYPE_VECTOR) 
			{
				string varName = (*paramDataHandle)[i]->name +  "1D";
				
				result += "int " + varName + "[1];\n";
				result += varName + "[0] = (" + (*paramDataHandle)[i]->partInf.sizeD1 + ");\n";
				result += (*paramDataHandle)[i]->name + ".registerSubWithStarPU(" + varName + ", 1);\n";
			}
			else if((*paramDataHandle)[i]->isPeppherType() == TYPE_MATRIX) 
			{
				string varName = (*paramDataHandle)[i]->name +  "2D";
				result += "int " + varName + "[2];\n";
				
				result += varName + "[0] = " + ( ((*paramDataHandle)[i]->partInf.partTypeD1==FIXED_PARTITION)? ("(" + (*paramDataHandle)[i]->partInf.sizeD1 + ")")  : "1") + ";\n";				
				result += varName + "[1] = " + ( ((*paramDataHandle)[i]->partInf.partTypeD2==FIXED_PARTITION)? ("(" + (*paramDataHandle)[i]->partInf.sizeD2 + ")") : "1") + ";\n";

				result += (*paramDataHandle)[i]->name + ".registerSubWithStarPU(" + varName + ", 2);\n";
			}
		}
	}
	return result;
}

void CG_ParamList::getLoopVariable(Param *p, string &first, string &second, bool doSeparate)
{
	DEBUG_METHOD_ENTRY("getLoopVariable") // used for debugging purposes to trace problems...
	
	if(doSeparate && p->dimensions==2)
		first = second = "-1";
	else
		first = second = "NA";
	
	if (p->partInf.dimensions < 1)
		error("The parameter is unpartition-able: "+ p->name+".");
	
	if(method->paramXPart && method->paramYPart)
	{
		string sizeD1 = p->partInf.sizeD1;
		string sizeD2 = p->partInf.sizeD2;
	
		string refSizeD1 = method->paramXPart->partInf.sizeD1;
		string refSizeD2 = method->paramYPart->partInf.sizeD2;
		
		if (p->partInf.dimensions == 2)
		{
			first = ((sizeD1 == refSizeD2)? "_y_":"_x_");
			second = ((sizeD2 == refSizeD1)? "_x_":"_y_");
		}
		else if (p->partInf.partTypeD1 == FIXED_PARTITION)
			first = ((sizeD1 == refSizeD2)? "_y_":"_x_");
		else if (p->partInf.partTypeD2 == FIXED_PARTITION)
		{
			if(doSeparate && p->dimensions==2)
				second = ((sizeD2 == refSizeD1)? "_x_":"_y_");
			else
				first = ((sizeD2 == refSizeD1)? "_x_":"_y_");
		}
	}
	else if (method->paramXPart)
	{
		if(p->partInf.dimensions>1) // may occur if partitioning is done on a wrong parameter
			error("The partitoning dimensions are wrong for parameter: "+ p->name + ". Partitioning parameter: "+method->paramXPart->name);
		first = "_x_";
	}
	else if (method->paramYPart)
	{
		if(p->partInf.dimensions>1) // may occur if partitioning is done on a wrong parameter
			error("The partitoning dimensions are wrong for parameter: "+ p->name + ". Partitioning parameter: "+method->paramYPart->name);
		if(doSeparate && p->dimensions==2)
			second = "_y_";
		else	
			first = "_y_";
	}
}


/** Calculate starpu data handle assignment string and accessMode e.g. task->buffers[0].handle =arr_handle; task->buffers[0].mode = STARPU_RW; */
string CG_ParamList::getTHBS2()
{
	DEBUG_METHOD_ENTRY("getTHBS2") // used for debugging purposes to trace problems...
	
	int size=paramDataHandle->size();
	string result=" ", handlename_,num;
	stringstream iss;
	string first, second;
	for(int i=0;i<size;++i)
	{
		iss.str("");
		iss<<i;
		num=iss.str();
		
		if((*paramDataHandle)[i]->partitionParam()) // if we need to do task partitioning
		{
			if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if not a peppher container
			{
				if( (*paramDataHandle)[i]->partInf.dimensions==1 ) // 1D partitioned vector/csr_matrix/matrix
				 {
				 	getLoopVariable((*paramDataHandle)[i], first, second);
				 	result += "task->handles["+num+"] = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 1, " + first + ");\n";
//				 	result += "task->buffers["+num+"].handle = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 1, " + first + ");\n";
				 } 
				else if( (*paramDataHandle)[i]->dimensions==2 ) // 2D partitioned matrix
				{
					getLoopVariable((*paramDataHandle)[i], first, second);
				 	
					if((*paramDataHandle)[i]->partInf.dimensions==2)
						result += "task->handles["+num+"] = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 2, " + first + " , " + second + ");\n";
//						result += "task->buffers["+num+"].handle = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 2, " + first + " , " + second + ");\n";
//					else if((*paramDataHandle)[i]->partInf.dimensions==1)
//						result += "task->buffers["+num+"].handle = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 1, " + first + ");\n";
//					else if((*paramDataHandle)[i]->partInf.partTypeD2==FIXED_PARTITION)
//						result += "task->buffers["+num+"].handle = starpu_data_get_sub_data(" + (*paramDataHandle)[i]->name + "_handle, 1, " + first + ");\n";
				}
			}
			else if((*paramDataHandle)[i]->isPeppherType() == TYPE_VECTOR) 
			{
				getLoopVariable((*paramDataHandle)[i], first, second);
				string varName = (*paramDataHandle)[i]->name +  "1D";
				result += varName + "[0] = " + first + ";\n";
				result += "task->handles["+num+"] = " + (*paramDataHandle)[i]->name + ".getSubHandle(" + varName + ", 1);\n";
//				result += "task->buffers["+num+"].handle = " + (*paramDataHandle)[i]->name + ".getSubHandle(" + varName + ", 1);\n";
			}
			else if((*paramDataHandle)[i]->isPeppherType() == TYPE_MATRIX) 
			{
				string varName = (*paramDataHandle)[i]->name +  "2D";
				
				getLoopVariable((*paramDataHandle)[i], first, second, true);
				
				result += varName + "[0] = " + first + ";\n";				
				result += varName + "[1] = " + second + ";\n";
				
				result += "task->handles["+num+"] = " + (*paramDataHandle)[i]->name + ".getSubHandle(" + varName + ", 2);\n";
//				result += "task->buffers["+num+"].handle = " + (*paramDataHandle)[i]->name + ".getSubHandle(" + varName + ", 2);\n";
			}
		}
		else // no data partitioning for this operand
		{
			if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if it is not a peppher container
				result += "task->handles["+num+"] = " + (*paramDataHandle)[i]->name + "_handle;\n";
//				result += "task->buffers["+num+"].handle = " + (*paramDataHandle)[i]->name + "_handle;\n";
			else
				result += "task->handles["+num+"] = " +  (*paramDataHandle)[i]->name + ".registerWithStarPU();\n"; 
//				result += "task->buffers["+num+"].handle = " +  (*paramDataHandle)[i]->name + ".registerWithStarPU();\n"; 
		}
		
		
//		if((*paramDataHandle)[i]->accessMode=="READWRITE") // readwrite mode
//			result += "task->buffers["+num+"].mode = STARPU_RW;\n";
//			
//		else if((*paramDataHandle)[i]->accessMode=="WRITE") // write mode
//			result += "task->buffers["+num+"].mode = STARPU_W;\n";
//		
//		else if((*paramDataHandle)[i]->accessMode=="READ") // read mode
//			result += "task->buffers["+num+"].mode = STARPU_R;\n";	
//		else
//			error("Some unknown access mode detected: "+ (*paramDataHandle)[i]->accessMode + ". Should be either read, readwrite or write.");
	}

	return result;
}



/** Calculate starpu data handle accessMode e.g. cl_vector_scale->modes[0] = STARPU_RW; */
string CG_ParamList::getCLMS2(std::string name)
{
	DEBUG_METHOD_ENTRY("getCLMS2") // used for debugging purposes to trace problems...
	
	string result1=name;
	int size=paramDataHandle->size();
	string result=" ",num;
	stringstream iss;
	for(int i=0;i<size;++i)
	{
		iss.str("");
		iss<<i;
		num=iss.str();
		
		if((*paramDataHandle)[i]->accessMode=="READWRITE") // readwrite mode
			result += result1 + ".modes["+num+"] = STARPU_RW;\n";
			
		else if((*paramDataHandle)[i]->accessMode=="WRITE") // write mode
			result += result1 + ".modes["+num+"] = STARPU_W;\n";
		
		else if((*paramDataHandle)[i]->accessMode=="READ") // read mode
			result += result1 + ".modes["+num+"] = STARPU_R;\n";	
		else
			error("Some unknown access mode detected: "+ (*paramDataHandle)[i]->accessMode + ". Should be either read, readwrite or write.");
	}

	return result;
}


// Calculate starpu_data_unregistration string, e.g. starpu_data_unregister(arr_handle); */
string CG_ParamList::getURDS2()
{
	DEBUG_METHOD_ENTRY("getURDS2") // used for debugging purposes to trace problems...
	
	int size=paramDataHandle->size();
	string result=" ", name_;
	for(int i=0;i<size;++i)
	{
		if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if it is not a peppher container
		{
			name_=(*paramDataHandle)[i]->name;

			if((*paramDataHandle)[i]->partitionParam()) // if we did task partitioning then need to unpartition data before unregistering
				result += "starpu_data_unpartition("+name_+"_handle, 0);\n";

			result += "starpu_data_unregister("+name_+"_handle);";
		}
	}
	return result;
}

/** Calculates the parameters registered to starpu for passing them to the function call e.g., STARPU_VECTOR_GET_PTR(...); ... */
string CG_ParamList::getPGB2(bool clType)
{
	DEBUG_METHOD_ENTRY("getPGB2") // used for debugging purposes to trace problems...
	
	int size=raw->size();
	string name_,type_, result=" ";
	if(size>0)
	{
        name_= (*raw)[0]->name;
		checkType( name_, type_);
		result+=stmtGen(name_, type_,clType);
	}
	for(int i=1;i<size;++i)
	{
		name_= (*raw)[i]->name;
		checkType( name_, type_);
		result+=","+stmtGen(name_, type_, clType);
	}
	
	return result;
}


/**  Calculate variable PCD1 based on successfully classified parameters. More detail of variable PCD1 see class PCD1.*/
string CG_ParamList::getPCD1()
{
	DEBUG_METHOD_ENTRY("getPCD1") // used for debugging purposes to trace problems...
	
	int size=paramDataHandle->size();
	string result = "";
	for(int i=0;i<size;++i)
	{
		string type_=(*paramDataHandle)[i]->type;
		string name = (*paramDataHandle)[i]->name + "_handle";
		string elemType = (*paramDataHandle)[i]->getElementType();
		
		if((*paramDataHandle)[i]->isPeppherType() == TYPE_VECTOR) // if it is a peppher Vector 
		{	
			result += type_ + "<"+ elemType + "> " + name +"((" + elemType + " *)STARPU_VECTOR_GET_PTR( (struct starpu_vector_interface *)buffers[" + convertIntToString(i) + "]), STARPU_VECTOR_GET_NX( (struct starpu_vector_interface *)buffers["+ convertIntToString(i) +"]) );\n";
			
		}
		else if ((*paramDataHandle)[i]->isPeppherType() == TYPE_MATRIX) // if it is a peppher Matrix
		{
			result += type_ + "<" + elemType + "> " + name +"((" + elemType + " *)STARPU_MATRIX_GET_PTR( (struct starpu_matrix_interface *)buffers[" + convertIntToString(i) + "]), STARPU_MATRIX_GET_NY( (struct starpu_matrix_interface *)buffers[" + convertIntToString(i) + "]), STARPU_MATRIX_GET_NX( (struct starpu_matrix_interface *)buffers[" + convertIntToString(i) + "]), STARPU_MATRIX_GET_LD( (struct starpu_matrix_interface *)buffers[" + convertIntToString(i) + "]) );\n";	
		}	
		else if ((*paramDataHandle)[i]->isPeppherType() == TYPE_VARIABLE_PTR) // if it is a peppher Variable pointer
		{
			result += type_ + "<" + elemType + "> " + name +"((" + elemType + " *)STARPU_VARIABLE_GET_PTR( (struct starpu_variable_interface *)buffers[" + convertIntToString(i) + "]), peppher::INSIDE_COMPONENT_CONTAINER );\n";	
		}		
	}
	return result;
}


/**  Determine whether the function call is asynchronous. */
bool CG_ParamList::isAsynchronousCall()
{
	DEBUG_METHOD_ENTRY("isAsynchronousCall") // used for debugging purposes to trace problems...

	int size=paramDataHandle->size();
	for(int i=0;i<size;++i)
	{
		if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if it is not a peppher container, then we need to unregister it immediately
		{
			return false;
		}
	}
	return true;
}




/**  Determine whether the task execution should be synchronous based on parameter list and task partitioning.*/
bool CG_ParamList::requireSynchronous()
{
	DEBUG_METHOD_ENTRY("requireSynchronous") // used for debugging purposes to trace problems...
	
	if(method->supportPartitioning) // if we did task partitioning then dont need synchronous execution
		return false;
		
	int size=paramDataHandle->size();
	for(int i=0;i<size;++i)
	{
		if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if it is not a peppher container, then we need to unregister it immediately
		{
			return true;
		}
	}
// following not possible now as Pointers are not passed as read only arguments.	
//	size=paramReadOnly->size();
//	for(int i=0;i<size;++i)
//	{
//		if((*paramReadOnly)[i]->isPointer) // if it is a pointer (although read only) then task should be synchronous due to data consistency problems
//		{
//			return true;
//		}
//	}
	return false;
}


/**  Determine whether the we need to make a blocking call to wait for all tasks to finish, due to task partitioning.*/
bool CG_ParamList::requireTaskWait()
{
	DEBUG_METHOD_ENTRY("requireTaskWait") // used for debugging purposes to trace problems...
	
	if(method->supportPartitioning)
	{
		int size=paramDataHandle->size();
		for(int i=0;i<size;++i)
		{
			if((*paramDataHandle)[i]->isPeppherType() == TYPE_OTHER) // if it is not a peppher container, then we need to have task wait
			{
				return true;
			}
		}
	}
	
	return false;
}

// Checks what is the type of parameter. This type is used to determine how it is registered and unregistered to/from StarPU.
void CG_ParamList::checkType(string name, string &type)
{
	DEBUG_METHOD_ENTRY("checkType") // used for debugging purposes to trace problems...
	
	if(exist(paramReadOnly,name))
		type="paramReadOnly";
	else if( exist(paramDataHandle,name) )
		type="paramDataHandle";
	else
		type="meta";
}


/** Checks whether a parameter with "name" exist in a ParamList */
bool CG_ParamList::exist(vector<Param*> *curr,string name_)
{
	DEBUG_METHOD_ENTRY("exist") // used for debugging purposes to trace problems...
	
	int size=curr->size();
	for(int i=0;i<size;++i)
		   if( (*curr)[i]->name==name_ ) return  1;
	return 0;
}


/** Generate the statement for getting data that is registered to StarPU to pass to the method. A helper method */
string CG_ParamList::stmtGen(string name, string type, bool clType)
{
	DEBUG_METHOD_ENTRY("stmtGen") // used for debugging purposes to trace problems...
	
	if(type=="paramDataHandle")
	{
		int num=getNum(paramDataHandle,name);
		string num_;
		stringstream iss;
		iss<<num;
		num_=iss.str();
		string type_=(*paramDataHandle)[num]->type;

		
		if((*paramDataHandle)[num]->isPeppherType() == TYPE_VECTOR) // if it is a peppher Vector 
		{
			string str = (*paramDataHandle)[num]->name + "_handle";
//			string elemType = (*paramDataHandle)[num]->getElementType();
//			string str = type_ + "<"+ elemType + ">(("+elemType+" *)"+"STARPU_VECTOR_GET_PTR( (struct starpu_vector_interface *)buffers["+num_+"]), STARPU_VECTOR_GET_NX( (struct starpu_vector_interface *)buffers["+num_+"]) )";
			return str;
		}
		else if ((*paramDataHandle)[num]->isPeppherType() == TYPE_MATRIX) // if it is a peppher Matrix
		{
			string str = (*paramDataHandle)[num]->name + "_handle";
//			string str = "("+type_+")"+"STARPU_MATRIX_GET_PTR"+"( (struct starpu_matrix_interface *)buffers["+num_+"])";
			return str;
		}
		else if ((*paramDataHandle)[num]->isPeppherType() == TYPE_VARIABLE_PTR) // if it is a peppher Variable
		{
			string str = (*paramDataHandle)[num]->name + "_handle";
			return str;
		}
		else if((*paramDataHandle)[num]->isScalar()) // scalar variable data type
		{
			if((*paramDataHandle)[num]->isPointer)
				return "("+type_+")"+"STARPU_VARIABLE_GET_PTR"+"( (struct starpu_variable_interface *)buffers["+num_+"])";
			else
			{
//				string str(type_);
//				removeSuffix(str,'*');
				return "(*(("+type_+" *)"+"STARPU_VARIABLE_GET_PTR"+"( (struct starpu_variable_interface *)buffers["+num_+"])))";
			}
		}
		else if( (*paramDataHandle)[num]->pType==TYPE_CSR_MATRIX ) // potential vector type
		{
			return "("+type_+")"+"STARPU_CSR_GET_NZVAL"+"( (struct starpu_csr_interface *)buffers["+num_+"])";
		}
		else if( (*paramDataHandle)[num]->dimensions==1 ) // potential vector type
		{
			if(clType)
				return "("+type_+")"+"STARPU_VECTOR_GET_DEV_HANDLE"+"( (struct starpu_vector_interface *)buffers["+num_+"])";
			else
				return "("+type_+")"+"STARPU_VECTOR_GET_PTR"+"( (struct starpu_vector_interface *)buffers["+num_+"])";
		}
		else if( (*paramDataHandle)[num]->dimensions==2 ) // potential matrix type
		{
			if(clType)
				return "("+type_+")"+"STARPU_MATRIX_GET_DEV_HANDLE"+"( (struct starpu_matrix_interface *)buffers["+num_+"])";
			else
				return "("+type_+")"+"STARPU_MATRIX_GET_PTR"+"( (struct starpu_matrix_interface *)buffers["+num_+"])";
		}
		else  
			error("Unknown operand operation detected in CG_ParamList::stmtGen method.");
	}
	else if(type=="meta")
	{	
		//get the first meta target and return statement by extracting that target
		int num_meta=getNum(raw,name);
		
		string name_target;
		MetaParamTypes mType;
	
		

		if(!(*raw)[num_meta]->getFirstMetaNameAndType(name_target, mType))
			error("Error in meta-data");
		
		int num_target = getNum(paramDataHandle,name_target);
		if(num_target<0)
		    error("Error in meta-data");	

		Param *target = (*paramDataHandle)[num_target];
		
		string num_;
		stringstream iss;
		iss<<num_target;
		num_=iss.str();
		switch(mType)
		{
			case CSR_SIZE_PARAM:
				return "STARPU_CSR_GET_NNZ( (struct starpu_vector_interface *)buffers["+num_+"])";
				
			case SIZE_PARAM:
				return "STARPU_VECTOR_GET_NX( (struct starpu_vector_interface *)buffers["+num_+"])";
				
			case MATRIX_LD_PARAM:
				return "STARPU_MATRIX_GET_LD( (struct starpu_vector_interface *)buffers["+num_+"])";
				
			case MATRIX_NROWS_PARAM:
				return "STARPU_MATRIX_GET_NY( (struct starpu_matrix_interface *)buffers["+num_+"])";
			
			case MATRIX_NCOLS_PARAM:
				return "STARPU_MATRIX_GET_NX( (struct starpu_matrix_interface *)buffers["+num_+"])";	
			
			case CSR_NROWS_PARAM:
				return "STARPU_CSR_GET_NROW( (struct starpu_csr_interface *)buffers["+num_+"])";	
			
			case CSR_FIRST_PARAM:
				return "STARPU_CSR_GET_FIRSTENTRY( (struct starpu_csr_interface *)buffers["+num_+"])";		
			
			case CSR_ROW_OFFSETS_PARAM:
				return "("+(*raw)[num_meta]->type+")STARPU_CSR_GET_ROWPTR( (struct starpu_csr_interface *)buffers["+num_+"])";	
			
			case CSR_COL_INDICES_PARAM:
				return "("+(*raw)[num_meta]->type+")STARPU_CSR_GET_COLIND( (struct starpu_csr_interface *)buffers["+num_+"])";		
			
			default:
				warn("Unknown metaparameter type occured. Generated code will possibly be erroneous");	
			
		}	
//		if((*raw)[num_meta]->metaTargetLdParam)
//		{
//			Param *target = (*raw)[num_meta]->metaTargetLdParam;
//			string name_target=target->name;
//			int num=getNum(paramDataHandle,name_target);
//			string num_;
//			stringstream iss;
//			iss<<num;
//			num_=iss.str();
//			return "STARPU_MATRIX_GET_LD( (struct starpu_vector_interface *)buffers["+num_+"])";
//		}
//		
//		// go for first operand as it does not matter because size parameter should be same
//		Param *target=( * (*raw)[num_meta]->metaTargetList->cg_paramList->list->begin() ); 
//	    if(target->metaDataList->cg_paramList->size()==1)
//		{
//			string name_target=target->name;
//			int num=getNum(paramDataHandle,name_target);
//			string num_;
//			stringstream iss;
//			iss<<num;
//			num_=iss.str();
//			return "STARPU_VECTOR_GET_NX( (struct starpu_vector_interface *)buffers["+num_+"])";
//		}
//		else if(target->metaDataList->cg_paramList->size()==2)
//		{
//			//calculate which buffer
//			string name_target=target->name;
//			int num=getNum(paramDataHandle,name_target);
//			//cout<<"TTTTT num:"<<num<<endl;
//			string num_;
//			stringstream iss;
//			iss<<num;
//			num_=iss.str();
//			//calculate NX or NY
//			int dimension=getNum( (*paramDataHandle)[num]->metaDataList->cg_paramList->list,  (*raw)[num_meta]->name);
//			
//			if(dimension <0 || dimension >1)
//				warn("Possible error: A parameter dimension can be either 1 or 2 side only, Given dimension: "+ convertIntToString(dimension) + ", parameter name: "+ name_target + ".\n");
//			
//			string api="STARPU_MATRIX_GET_NX";
//			if(dimension==0)
//				api="STARPU_MATRIX_GET_NY";
//			return api+"( (struct starpu_matrix_interface *)buffers["+num_+"])";
//		}
//		
//		fatal("3 dimension matrix not supported, please contact developer to add this feature.");
		return "not developed";
	}
	else if(type=="paramReadOnly")
	{
		string result=env.message;
		return "(("+result+" *)_args)->"+name;
	}
}

/**  Get index of the parameter with "name" in the "curr" list. */
int CG_ParamList::getNum(vector<Param*> *curr,string name_)
{
	DEBUG_METHOD_ENTRY("getNum") // used for debugging purposes to trace problems...
	
	int size=curr->size();
	for(int i=0;i<size;++i)
		   if( (*curr)[i]->name==name_ ) return  i;
	return -1;
};



/** To display the list, A helper method calls by showAllList() */
void CG_ParamList::showList(vector<Param*> *list)
{
	DEBUG_METHOD_ENTRY("showList") // used for debugging purposes to trace problems...
	
	vector<Param*>::iterator it;
	string space="  ";
	for(it=list->begin();it!=list->end();++it)
		(*it)->show(space);
}


/** To display all lists */
void CG_ParamList::showAllList()
{
	DEBUG_METHOD_ENTRY("showAllList") // used for debugging purposes to trace problems...
	
	cout<<"/******************************************/"<<endl;
	cout<<"list: "<<endl;
	showList(list);
	cout<<endl<<"raw: "<<endl;
	showList(raw);
	cout<<endl<<"indep: "<<endl;
	showList(indep);
	cout<<endl<<"paramReadOnly: "<<endl;
	showList(paramReadOnly);
	cout<<endl<<"paramDataHandle: "<<endl;
	showList(paramDataHandle);
	cout<<"/******************************************/"<<endl;
}


