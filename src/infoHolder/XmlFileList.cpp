#include <iostream>
#include <XmlFileList.h>

using namespace std;

void XmlFileList::add(XmlFile *x)
{
	xmlFiles.push_back(x);
}

void XmlFileList::show()
{
	vector<XmlFile *>::iterator it;
	cout<<"XmlFileList contains: "<<endl;
	for ( it=xmlFiles.begin() ; it < xmlFiles.end(); it++ )
		(*it)->show();
}

vector<XmlFile *>::iterator XmlFileList::getBegin()
{
	return xmlFiles.begin();
}

vector<XmlFile *>::iterator XmlFileList::getEnd()
{
	return xmlFiles.end();
}

