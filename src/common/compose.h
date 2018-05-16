
//#include <Cpp_Lib.h>
#include <vector>



//Interface
/*{{{*/
#define GET_MACRO(_1,_2,_3, NAME,...) NAME
#define compose(...) GET_MACRO(__VA_ARGS__, compose3, compose2)(__VA_ARGS__)
/*}}}*/

//Built-in index: _index
//make index neutral to input and output
	//BOOST_STATIC_ASSERT((  boost::is_same< decltype(_in), decltype(_out)>::value  )); 
	//disable for now, hard to ensure type safety between a scalar and an array
	//Seems to me to ensure type safefy is either write a static analysis,
	//or wrap the native array as new type with additional metadata
	//So far for the trade-off between powerful and safety, I choose
	//powerful for now.

//CPU Skeletons
/*{{{*/
#define compose2(_in, _kernel) \
	{ \
	auto _size=std::end(_in)-std::begin(_in); \
	for (auto _index = 0; _index != _size; ++_index) { \
		_kernel; \
	}}  

#define compose3(_in, _out, _kernel) \
	{ \
	auto _size=std::end(_in)-std::begin(_in); \
	for (auto _index = 0; _index != _size; ++_index) { \
		_kernel; \
	}}
	/*}}}*/

//Skeletons On OpenMP and CUDA
/*{{{*/

//It seems impossible to generate openmp implementation,
//by using macro, can not embed #pragma, # is illegal here
//Thus, you need source to source compiler,
//to implement the macro expansion yourself,
//thus you can insert the #pragma as you wish

//compose() //Default to CPU

//#pragma skepu_omp
//compose()

//#pragma skepu_cuda
//compose()


/*}}}*/





//std::for_each(std::begin(_data),std::end(_data),  [](decltype(_data[0]) &_tdata){_kernel;} )

//The parameter convention:
//the last one: always code snippet
//others are inputs and outputs
//but we don't distinguish them as inputs and outputs
//the user knowns that
