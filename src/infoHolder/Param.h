#ifndef PARAM_
#define PARAM_

#include <string>
#include <cg_helpers/ParamTypeHelper.h>


class ParamList;

enum PartitionTypes { NO_PARTITION, TUNABLE_PARTITION, FIXED_PARTITION };


enum MetaParamTypes { SIZE_PARAM, CSR_SIZE_PARAM, MATRIX_LD_PARAM, MATRIX_NROWS_PARAM,  MATRIX_NCOLS_PARAM, SIZE_EXPR_PARAM, CSR_NROWS_PARAM, CSR_FIRST_PARAM, CSR_ROW_OFFSETS_PARAM, CSR_COL_INDICES_PARAM, INVALID_META_PARAM };


struct CSRInfo
{
	std::string nrows;
	std::string rowOffsets;
	std::string colIndices;
	std::string first;
};

struct PartitionInf
{
	int dimensions;
	std::string rawString;
	PartitionTypes partTypeD1; // May use map<PartitionTypes, unsigned> in future but partition dimensions are restricted to 1 or 2 for now.
	std::string sizeD1;
	PartitionTypes partTypeD2;
	std::string sizeD2;
	
	PartitionInf() : dimensions (0), rawString(""), partTypeD1(NO_PARTITION), sizeD1(""), partTypeD2(NO_PARTITION), sizeD2("")
	{   }
};


/** @addtogroup group2
*
* @{
*/
/** @brief Intermediate Representation for a single parameter. */
class Param
{
	
private:
	void processPartition(std::string partitionInf_);
	
public:
	/**  Constructor, assign member variables by parameters.*/
	Param(std::string name_, std::string type_, std::string elemType_, std::string partitionInf_, std::string acc, std::string num, std::string _csrNRows, std::string _csrRowOffsets, std::string _csrColIndices, std::string _csrFirst, bool _dummy=false);
	
	Param(Param *p);
	
	/** Method used to calculate the "dimension" variable of the parameter, called by ParameterList after creating all parameters. */
	void calculateDimensions();
	
	/** show content of this class, used for debug.*/
	void show(std::string space);
	
	/** show name field of this class, used for debug.*/
	void showName();
	
	/**  Print info of Param, used for verbose mode. */
	void printMe();

	/**  Parameter name, such as "arr" */
	std::string name;
	
	/**  Parameter type, such as "int". */
	std::string type;
	
	/** To mark dummy variables */
	bool dummy;
	
	/** To decide whether parameter can be partitioned */
	bool partitionParam();
	
	/**  Partitioning information for a parameter, can be used to partition tasks and create several subtasks */
	PartitionInf partInf;
	
	/**  Parameter element type, required if the parameter is a PEPPHER container which can store elements of different types */
	std::string elemType;
	
	/**  Access mode, such as "readwrite". Stored in uppercase such as READWRITE */
	std::string accessMode;
	
	/**  Number of elements if this parameter is an array. More detail see example vector scale or matrix multiplication. */
	std::string numElements;
	
	/**  If this parameter is an array, this list contains parameters which describe sizes of this parameter. */
	ParamList *metaDataList;
	
	/**  If this parameter describe a size of other parameter, this list contains pointers to that parameter.*/
	ParamList *metaTargetList;
	
//	Param *metaSourceLdParam;
//	
//	Param *metaTargetLdParam;
	
	/** return whether this operand type is a scalar type */
	bool isScalar(); 
	
	/** return whether this operand type is a PEPPHER type */
	ParamTypeEnum isPeppherType(); 
	
	/** return the element type if param is of PEPPHER container type which are template containers */
	std::string getElementType();
	
	/** to determine if it is a pointer operand then starpu data registering could be a bit different */
	bool isPointer;
	
	/** the dimensions of the parameter, Is it 1D, 2D or scalar value. */
	int dimensions;
	
	
	void setMetaType(std::string name, MetaParamTypes type);
	
	void removeMetaType(std::string name, MetaParamTypes type);
	
	void removeMetaType(std::string name);
	
	bool getMetaType(std::string name, MetaParamTypes type);
	
	
	std::string csrNRows;
	std::string csrRowOffsets;
	std::string csrColIndices;
	std::string csrFirst;
	
	
	bool getFirstMetaNameAndType(std::string &name, MetaParamTypes& mType)
	{
		name="";
		mType = INVALID_META_PARAM;
		std::multimap<std::string, MetaParamTypes>::iterator it = metaTypeMap.begin();
		if(it!=metaTypeMap.end())
		{
			mType = it->second;
			name = it->first;
			return true;
		}
		std::cerr<<"check 1***\n";
		return false;
	}
	
	
	/** If params is actually a CSR Vector then it should have */
//	CSRInfo *csrInf;	
	
	/** The type of the meta param */
	std::multimap<std::string, MetaParamTypes> metaTypeMap;
	
	
	ParamTypeEnum pType;
};
/** @} */
#endif

