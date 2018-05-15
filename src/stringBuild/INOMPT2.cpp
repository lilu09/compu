#include <iostream>
#include <string>
#include <INOMPT2.h>

#include <helperFactory.h>

using namespace std;


string INOMPT2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...

	if(com->hasOpenMPImpl())
	{
		return "omp_set_num_threads(starpu_combined_worker_get_size());";
	}
	return "";
}

