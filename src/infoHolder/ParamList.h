#ifndef PARAMSLIST_
#define PARAMLIST_

#include <vector>
#include <Param.h>
#include <cg_helpers/CG_ParamList.h>
#include <methods.h>
#include <Node.h>

/** @addtogroup group2
*
* @{
*/
/** @brief  Intermediate Representation for a parameter list of one single function. */
class ParamList
{
public:
	/**  Default constructor, with nothing in it. */
	ParamList();
	
	/** Initialize a parameter list from a syntax tree of interface kind. This method is useful for building Intermediate Representation. */
	ParamList(Node *aTree, Method *method_);
	
	/** Initialize a parameter list from another ParameterList. This method is useful for building Intermediate Representation. */
//	ParamList(ParamList *aParam);
	
	/**  Add a Param to this container. */
	void addCG(Param *p);
	
	Param *getMetaType(std::string name, MetaParamTypes type);
	
	/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented.*/
	std::vector<Param *>::iterator getBegin();
	
	/**  Get iterator at end. This method is useful for traversing this list and hide how list is implemented.*/
    std::vector<Param *>::iterator getEnd();
	
	/** Show contents of all vectors, used for debug. */
	void showAllList();
	
	/**  Calculate variable ROPD1 based on successfully classified parameters. More detail of variable ROPD1 see class ROPD1. */
	std::string getROPD1();
	
	/**  Calculate variable IPL1 based on successfully classified parameters. More detail of variable IPL1 see class IPL1.*/
	std::string getIPL1();
	
	/**  Calculate variable ROAA2 based on successfully classified parameters. More detail of variable ROAA2 see class ROAA2.*/
	std::string getROAA2(std::string infName);
	
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
	
	/**  Determine whether the we need to make a blocking call to wait for all tasks to finish, due to task partitioning.*/
	bool requireTaskWait();
   
	/**  Handler to code generation class. */
	CG_ParamList *cg_paramList;
	
private:	
	/**  Container for Params. */
	std::vector<Param *> params;
};
/** @} */
#endif

