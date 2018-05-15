#include <iostream>
#include <string>
#include <CKN2.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>
#include <ComConfig.h>

using namespace std;


string CKN2::getResult(Node *tree)
{
	DEBUG_METHOD_ENTRY("getResult(Node)") // used for debugging purposes to trace problems...
	
	InfContainer *srcName=fetchTreeIterTwo(env.kb["CKN2"],tree);
	 string curr="", tmp;
	 stringstream iss;
	 char c;
	 int size=srcName->inf.size();
	 for(int i=0;i<size;++i)
	 {
		 curr=srcName->inf[i];
		 iss.clear();

		 iss.str(trimSpaces(curr));
		 while(iss.good())
		 {
			 if(iss.peek()=='.')
				 break;
			 iss>>c;
		 }
		 iss>>tmp;
		 if(tmp==".c" || tmp==".cpp")
		 {
			  iss>>curr;
			  break;
		 }
	 }
	 return curr;
}

string CKN2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	return com->configure->get("OPENCL")->cdltInfo->cl_kernel;
}

