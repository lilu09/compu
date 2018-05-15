#include <iostream>
#include <Element.h>

using namespace std;


Element::Element(string s) :Node(s),content(""){}

void Element::addattr(std::string attr_name, std::string attr_value)
{
	DEBUG_METHOD_ENTRY("addattr") // used for debugging purposes to trace problems...
	
	attrs.insert(map<string,string>::value_type (attr_name, attr_value));
}

void Element::print() 
{
	DEBUG_METHOD_ENTRY("print") // used for debugging purposes to trace problems...
	
	cout<<"+----------------------------------------------+"<<endl;
    cout<<"	  Node: "<<tag<<endl;
	if(father!=0)
		cout<<"	       Father: "<<father->tag<<endl;
	else
		cout<<"	       Father: "<<"No father!"<<endl;

   vector<Node *>::iterator  iter;
   for(iter = child.begin(); iter != child.end(); iter++)
	{
       cout<<"	       Child: "<<(*iter)->tag<<endl;
	}
   map<string, string>::iterator  iter2;
   for(iter2 = attrs.begin(); iter2 != attrs.end(); iter2++)
	{
       cout<<"	       Attribute_name: "<<iter2->first;
	   cout<<"	       Attribute_value: "<<iter2->second<<endl;
	}

	if(content!="")
	   cout<<"	       Content_value: "<<content<<endl;
	

	cout<<"+----------------------------------------------+"<<endl<<endl<<endl<<endl;
    
	for(iter = child.begin(); iter != child.end(); iter++)
		(*iter)->print();
}

