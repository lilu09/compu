#include <iostream>
#include <sstream>
#include <Node.h>

using namespace std;


Node::Node(string s) : tag(s),father(0){}
Node::Node(string s,Node *f) : tag(s),father(f){}



void Node::addchild(Node *node)
{
	DEBUG_METHOD_ENTRY("addchild") // used for debugging purposes to trace problems...
	
	node->father=this;
    //test if used, then add instanceNum, then add a different name
	//otherwise add normally , add instanceNum
	stringstream iss;
	iss<<child.size();
	int found_=0;
	vector<Node *>::iterator  iter;
	for(iter = child.begin(); iter != child.end(); iter++)
		if((*iter)->tag==node->tag)
			found_=1;
	if(found_)
		node->tag += iss.str();

	child.push_back(node);
	
}

bool Node::existChild(string key)
{
	DEBUG_METHOD_ENTRY("existChild(string)") // used for debugging purposes to trace problems...
	
	if(existChild())
	{
		vector<Node *>::iterator it;
		for(it=child.begin();it!=child.end();++it)
		{
			if( (*it)->tag==key )
				return 1;
		}
	}
	return 0;
}

bool Node::existChild()
{
	DEBUG_METHOD_ENTRY("existChild()") // used for debugging purposes to trace problems...
	
	return (child.size()!=0);
}

Node *Node::getChild(string s)
{
	DEBUG_METHOD_ENTRY("getChild(string)") // used for debugging purposes to trace problems...
	
	if(existChild())
	{
		vector<Node *>::iterator it;
		for(it=child.begin();it!=child.end();++it)
		{
			if( (*it)->tag==s )
				return (*it);
		}
	}
	return 0;
}

void Node::print() 
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
	cout<<"+----------------------------------------------+"<<endl<<endl<<endl<<endl;
    
	for(iter = child.begin(); iter != child.end(); iter++)
		(*iter)->print();

}

