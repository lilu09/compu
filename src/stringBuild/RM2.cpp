#include <iostream>
#include <string>
#include <RM2.h>
#include <CompileStmtList.h>

using namespace std;


string RM2::getResult(EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	CompileStmtList stmt(com);
	return stmt.getRM2();
}

