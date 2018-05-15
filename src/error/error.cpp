#include <iostream>
#include <stdlib.h>
#include <string>
#include <error.h>
#include <EnvVar.h>

using namespace std;
extern EnvVar env;

void fatal(string message)
{
	cout<<"Fatal Error: "<<message<<"!"<<endl;
	cout<<"Translation aborted!!!"<<endl;
	exit(0);
}

void error(string message)
{
	cout<<"Error: "<<message<<"!"<<endl;
	cout<<"Translation stopped!!!"<<endl;
	exit(0);
}

void warn(string message, REPORT_LEVEL rl)
{
	if(rl>REPORT_LEVEL_2)
	{
	  if(env.verboseLevel>1)
	  {
		cout<<"Warning: "<<message<<endl;
		cout<<"Translation continued!!!"<<endl;
	  }
	  return;
	}
	else if(rl>REPORT_LEVEL_1)
	{
	  //#ifdef WARN_DETAIL_LEVEL
	  if(env.verboseLevel>0)
	  {
		cout<<"Warning: "<<message<<endl;
		cout<<"Translation continued!!!"<<endl;
	  }
	  //#endif
	  return;
	}
	else
	{
		cout<<"Warning: "<<message<<endl;
		cout<<"Translation continued!!!"<<endl;
	}
}

void test(string message)
{
	cout<<"##### "<<message<<" ####"<<endl;
}

