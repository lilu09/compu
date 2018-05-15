#include <iostream>
#include <string>
#include <LKS2.h>

#include <helperFactory.h>
#include <InfContainer.h>
#include <methods.h>
#include <ComConfig.h>

using namespace std;


string LKS2::getResult(Node *tree)
{
	 DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...
	
	 InfContainer *srcName=fetchTreeIterTwo(env.kb["LKS2"],tree);

	 string curr="", tmp;
	 stringstream iss;
	 char c;
	 int size=srcName->inf.size();
	 for(int i=0;i<size;++i)
	 {
		 curr=srcName->inf[i];
		 iss.clear();
		 iss.str(curr);
		 while(iss.good())
		 {
			 if(iss.peek()=='.')
				 break;
			 iss>>c;
		 }
		 iss>>tmp;
		 if(tmp==".cl")
		 {
			  iss>>curr;						  
			 break;
			
		 }
	 }
	return curr;
}

string LKS2::getResult(Component *com)
{
	return com->configure->get("OPENCL")->cdltInfo->kernel;
}

