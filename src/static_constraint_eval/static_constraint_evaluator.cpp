

#include <static_constraint_evaluator.hpp>
#include <EnvVar.h>

extern EnvVar env;

static inline bool bash_exe (const std::string& cmd,std::vector<std::string>& out ) {
    FILE*           fp;
    const int       SIZEBUF = 1234;
    char            buf [SIZEBUF];
    out = std::vector<std::string> ();
    if ((fp = popen(cmd.c_str (), "r")) == NULL) {
        return false;
    }
    std::string  cur_string = "";
    while (fgets(buf, sizeof (buf), fp)) {
        cur_string += buf;
    }
    out.push_back (cur_string.substr (0, cur_string.size () - 1));
    pclose(fp);
    return true;
}

bool static_constraint_evaluator(const std::string& expr, const std::string& lib_prepare){

	assert(expr!="");

	std::string cmd =  env.static_constraint_eval_path + "/static_constraint_evaluator.sh '" + expr + "' "
		+ "'" + lib_prepare + "'"; ;

	std::vector<std::string> output; 
	assert( bash_exe(cmd, output) );

	return static_cast<bool>( std::stoi( output[0] ) );

}

//int main(int argc, const char *argv[])
//{

	//std::string expr="xpdl::machine::num_gpus > 0";

	//bool x=static_constraint_evaluator(expr);

	//std::cout<<x<<std::endl;
	
	//return 0;
//}

