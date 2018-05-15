#include <iostream>
#include <string>
#include <MNOMPT2.h>

#include <helperFactory.h>

using namespace std;


string MNOMPT2::getResult(Component *com)
{
	DEBUG_METHOD_ENTRY("getResult") // used for debugging purposes to trace problems...

	if(com->hasOpenMPImpl())
	{
		return "#include <omp.h>\n\n int get_omp_num_threads() \n{\n\t return starpu_combined_worker_get_size(); \n}\n";
	}
	return "";
}

