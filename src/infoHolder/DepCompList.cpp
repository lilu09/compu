#include <DepCompList.h>

using namespace std;

void DepCompList::add(DepComp *p)
{
	list.push_back(p);
}

/** locate iterator to the first element of list field*/
vector<DepComp *>::iterator DepCompList::getBegin()
{
	return list.begin();
}

/** locate iterator to the last element of list field*/
vector<DepComp *>::iterator DepCompList::getEnd()
{
	return list.end();
}

