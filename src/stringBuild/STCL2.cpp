#include <iostream>
#include <string>
#include <STCL2.h>
#include <helperFactory.h>


using namespace std;


void STCL2::findParam(std::string accessMode, ParamList *paramList, Param *&p)
{
		
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

string STCL2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	string result = "";

	Method *m = com->intfc->methods->getFirst();	
	if(!m)
		error("No method definition in Interface XML file!!!");
	
	if(m->paramXPart || m->paramYPart) // This is done to make it compatible with C90 standard where you can't have e.g. for(int x = 0...)
	{
		if(!m->paramXPart) // only y-part exists
			result += "int _y_;\n";
		else if(!m->paramYPart) // only x-part exists
			result += "int _x_;\n";	
		else // both x and y-part exists
			result += "int _x_,_y_;\n";		
	}
	if(m->paramXPart)
	{
		if(m->paramXPart->isPeppherType() != TYPE_OTHER)
			result += "for(_x_=0; _x_< (" + m->paramXPart->name + ".totalPartitions()); _x_++)\n";
		else // if(m->paramXPart->metaDataList->cg_paramList->size()==1 ) // vector
		{
			string meta_ = (* m->paramXPart->metaDataList->cg_paramList->list)[0]->name;
			result += "for(_x_=0; _x_< (" + meta_ + "/ (" + m->paramXPart->partInf.sizeD1 + "));  _x_++)\n";
		}
	}
	if(m->paramYPart)
	{
		if(m->paramYPart->isPeppherType() != TYPE_OTHER)
			result += "for(_y_=0; _y_< (" + m->paramXPart->name + ".totalPartitions(2)); _y_++)\n";
		else // if(m->paramXPart->metaDataList->cg_paramList->size()==1 ) // vector
		{
			string meta_ = (* m->paramXPart->metaDataList->cg_paramList->list)[1]->name;
			result += "for(_y_=0; _y_< (" + meta_ + "/ (" + m->paramXPart->partInf.sizeD2 + "));  _y_++)\n";
		}
	}
		
	return result;
}

