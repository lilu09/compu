#include <DepComp.h>

using namespace std;

DepComp::DepComp()
{
	
}

DepComp::DepComp(string inf,string xml):infName(inf),xmlName(xml)
{
	
}

void DepComp::show()
{
	cout<<"infName: "+infName+"   xmlName: "+xmlName<<endl;
}

