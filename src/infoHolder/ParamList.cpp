#include <ParamList.h>
#include <Element.h>
#include <error.h>



using namespace std;

ParamList::ParamList() : cg_paramList(new CG_ParamList())
{
	
}

ParamList::ParamList(Node *aTree, Method *method_): cg_paramList(new CG_ParamList(aTree, method_))
{
	vector<Param*>::iterator it;
	for(it=cg_paramList->raw->begin();it!=cg_paramList->raw->end();++it)
	{
		params.push_back(new Param(*it));
	}
}



Param *ParamList::getMetaType(std::string name, MetaParamTypes type)
{
	vector<Param*>::iterator it;
	for(it=cg_paramList->list->begin();it!=cg_paramList->list->end();++it)
	{
		if((*it)->getMetaType(name, type))
			return *it;
	}
	return 0;
}
//ParamList::ParamList(ParamList *pal): cg_paramList(new CG_ParamList(pal))
//{
//	
//}

void ParamList::addCG(Param *p)
{
	cg_paramList->list->push_back(p);
}

vector<Param *>::iterator ParamList::getBegin()
{
	return params.begin();
}

vector<Param *>::iterator ParamList::getEnd()
{
	return params.end();
}



string ParamList::getROPD1()
{
	return cg_paramList->getROPD1();
}

string ParamList::getIPL1()
{
	return cg_paramList->getIPL1();
}

string ParamList::getROAA2(string infName)
{
	return cg_paramList->getROAA2(infName);
}


string ParamList::getIWVN2()
{
	return cg_paramList->getIWVN2();
}

string ParamList::getHD2()
{
	return cg_paramList->getHD2();
}

string ParamList::getDRS2()
{
	return cg_paramList->getDRS2();
}

string ParamList::getTHBS2()
{
	return cg_paramList->getTHBS2();
}

string ParamList::getCLMS2(std::string name)
{
	return cg_paramList->getCLMS2(name);
}

string ParamList::getURDS2()
{
	return cg_paramList->getURDS2();
}

string ParamList::getPGB2(bool clType)
{
	return cg_paramList->getPGB2(clType);
}

string ParamList::getPCD1()
{
	return cg_paramList->getPCD1();
}

/**  Determine whether the task execution should be synchronous based on parameter list.*/
bool ParamList::requireSynchronous()
{
	return cg_paramList->requireSynchronous();
}

/**  Determine whether the we need to make a blocking call to wait for all tasks to finish, due to task partitioning.*/
bool ParamList::requireTaskWait()
{
	return cg_paramList->requireTaskWait();
}	


void ParamList::showAllList()
{
	cg_paramList->showAllList();
}

