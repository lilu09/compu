#ifndef CG_PARAMSLIST_
#define CG_PARAMSLIST_

#include <vector>
#include <Param.h>
#include <methods.h>
#include <Node.h>



class ParamList;

class Method;

/** @addtogroup group2
*
* @{
*/
/** @brief  Intermediate Representation for a parameter list of one single function. */
class CG_ParamList
{
private:
	void getLoopVariable(Param *p, std::string &first, std::string &second, bool doSeparate=false);
public:
	/**  Default constructor, with nothing in it. */
	CG_ParamList();
	
	/** Initialize a parameter list from a syntax tree of interface kind. This method is useful for building Intermediate Representation. */
	CG_ParamList(Node *aTree, Method *method_);
	
 	/** Add a Param to a vector<Param*>*/
	void add(std::vector<Param*> *p,Param* curr);
	
	/**  Add a Param to this container. */
	void add(Param *p);
	
	/**  Get size of member variable list. */
	int size();
	
	/**  Lookup Param by name.*/
	Param *lookupByName(std::vector<Param*> *curr,std::string name_, bool throwError = true);
	
	/**  Test if a container contains a member called name. */
	bool exist(std::vector<Param*> *curr,std::string name);
	
	/**  Get ordinal number of parameter called name in a list. */
	int getNum(std::vector<Param*> *curr,std::string name);
	
	/** Creating object for class fields of pointer type*/
	void initMember();
	
	/** Stub for constructor ParamList(Node *aTree)*/
	void initFromNode();
	
	/**  Copy all parameters into container raw, retaining their original info. Target is pointer to Compile statement Element in syntax tree. This method is useful for building Intermediate Representation. */
	void updateValue(Node *target);
		
	/**  Update metaDataList and metaTargetList field of class Param. This method is useful for building relationship between parameters. Target is  pointer to Compile statement Element in syntax tree. This method is useful for building Intermediate Representation. */
	void updateMeta(Node *target);
	
	void updateCSRMeta();
	
	void updateMetaLdParam(Node *target);
	
	/**  Copy independent parameters to field indep. Independent parameter means all parameters except those who decribe size of others. This info is useful for StarPU because only Independent variable should be transfered by StarPU.*/
	void updateIndep();
	
	/**  Copy independent parameters that are read to readOnly field and other independent parameters to readwrite. This info is useful for StarPU to choose the way it transfer data.*/
	void classify();
	
	/**  Check if parameter called name is readonly, read or that which describe size of others.*/
	void checkType(std::string name, std::string &type);
	
	/**  Generate a statement that adapt normal parameter to that demanded by StarPU.*/
	std::string stmtGen(std::string name, std::string type, bool clType=false);
	
	/** Show contents of one specific vector, used for debug. */
	void showList(std::vector<Param*> *list);
	
	/** Show contents of all vectors, used for debug. */
	void showAllList();
	
	/**  Calculate variable ROPD1 based on successfully classified parameters. More detail of variable ROPD1 see class ROPD1. */
	std::string getROPD1();
	
	/**  Calculate variable IPL1 based on successfully classified parameters. More detail of variable IPL1 see class IPL1.*/
	std::string getIPL1();
	
	/**  Calculate variable ROAA2 based on successfully classified parameters. More detail of variable ROAA2 see class ROAA2.*/
	std::string getROAA2 (std::string infName);
	
	/**  Calculate variable IWVN2 based on successfully classified parameters. More detail of variable IWVN2 see class IWVN2.*/
	std::string getIWVN2();
	
	/**  Calculate variable HD2 based on successfully classified parameters. More detail of variable HD2 see class HD2.*/
	std::string getHD2();
	
	/**  Calculate variable DRS2 based on successfully classified parameters. More detail of variable DRS2 see class DRS2.*/
	std::string getDRS2();
	
	/**  Calculate variable THBS2 based on successfully classified parameters. More detail of variable THBS2 see class THBS2.*/
	std::string getTHBS2();
	
	/**  Calculate variable CLMS2 based on successfully classified parameters. More detail of variable CLMS2 see class CLMS2.*/
	std::string getCLMS2(std::string name);
	
	/**  Calculate variable URDS2 based on successfully classified parameters. More detail of variable URDS2 see class URDS2.*/
	std::string getURDS2();
	
	/**  Calculate variable PGB2 based on successfully classified parameters. More detail of variable PGB2 see class PGB2.*/
	std::string getPGB2(bool clType=false);
	
	/**  Calculate variable PCD1 based on successfully classified parameters. More detail of variable PCD1 see class PCD1.*/
	std::string getPCD1();
	
	/**  Determine whether the task execution should be synchronous based on parameter list.*/
	bool requireSynchronous();
	
	/**  Determine whether the function call is asynchronous. */
	bool isAsynchronousCall();
	
	/**  Determine whether the we need to make a blocking call to wait for all tasks to finish, due to task partitioning.*/
	bool requireTaskWait();
    
    /**  This field saves parameter list passed from type conversion constructor.*/
	ParamList *paraList;
	
	/**  This field is default container for this class. Used for storing data related to meta-data and meta-target list. 
	*    If no container specified, list will be used. */
	std::vector<Param*> *list;
	
	/**  This field stores original form of parameters. */
	std::vector<Param*> *raw;  
	
	/**  This field strores only independent variables. Independent parameter means all parameters except those who decribe size of others. This info is useful for StarPU because only Independent variable should be transfered by StarPU.*/
	std::vector<Param*> *indep;
	
	/**  This field stores independent variables that are passed as a part of read only codelet arguments in StarPU. Used for passsing read-only scalar values right now. */
	std::vector<Param*> *paramReadOnly;
	
	/**  This field stores independent variables that are passed by registering data handle with StarPU. */
	std::vector<Param*> *paramDataHandle;
	
	/**  This field saves syntax tree passed by constructor ParamList(Node *aTree). */
	Node *tree;
	
	/** The method to which this parameterlist belongs. Useful for accessing some properties of method class. */
	Method *method;
    
};
/** @} */
#endif

