#include <MethodList.h>

using namespace std;

void MethodList::add(Method *m)
{
	methods.push_back(m);
}

void MethodList::printMe()
{
	vector<Method *>::iterator it;
	for(it=methods.begin();it!=methods.end();++it)
	{
		(*it)->printMe();
	}
}

Method *MethodList::getFirst()
{
	if(methods.size()>0)
		return methods[0];
		
	warn("No Method found MethodList::getFirst() method: returning NULL");	
	return 0;
}

