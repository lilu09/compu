#include <iostream>
#include <XmlFile.h>

using namespace std;

XmlFile::XmlFile()
{
};

XmlFile::XmlFile(string fn):filename(fn)
{
};

void XmlFile::show()
{
	cout<<"filename: "+filename<<endl;
}

