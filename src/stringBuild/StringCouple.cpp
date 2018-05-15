
#include <iostream>
#include <string>
#include <StringCouple.h>
#include <Component.h>
#include <EntryComponent.h>
#include <Helper.h>
#include <helperFactory.h>

using namespace std;

StringCouple::StringCouple(string k,string v):key(k),value(v){}

void StringCouple::change(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult (Node)") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper(key);
	if(helper)
	{
		value=helper->getResult(com);
		delete helper;
	}
	else
	{
		warn("No helper found in StringCouple::change(Component *com) for key: "+key);
		value="No helper found";
	}
}

void StringCouple::change(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	Helper *helper=helperFactory::createHelper(key);
	if(helper)
	{
		value=helper->getResult(com);
		delete helper;
	}
	else
	{
		warn("No helper found in StringCouple::change(EntryComponent *com) for key: "+key);
		value="No helper found";
	}
}

