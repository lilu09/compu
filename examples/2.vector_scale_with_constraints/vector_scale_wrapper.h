

 #ifndef VECTOR_SCALE_WRAPPERR
 #define VECTOR_SCALE_WRAPPERR

 //#include <map>
 //#include <string>
 //#include <iostream>
 //#include <stdlib.h>

 //using namespace std;

 // to assign tag ids which can be used later for wait etc.
 //static unsigned PEPPHER_tagId = 0;

 // can use this to track data_handle and not create data_handle each time it is used. But how could we take care when to release data_handle?
 //std::map<std::string, starpu_data_handle_t> dataHandles;

 typedef struct 
{
	float factor;
} ROA_vector_scale;

 typedef struct 
{
	struct starpu_codelet cl_vector_scale;
	
	 int cl_vector_scale_init;
} struct_vector_scale;



 // include statement

 // extern statement
 extern void scale_cpu_func( float * arr, int size, float factor);

 //OpenMP method, If used



 void scale_cpu_func_wrapper (void *buffers[], void *_args)
 {
 /* peppher container declarations, if any */




 scale_cpu_func (
  (float *)STARPU_VECTOR_GET_PTR( (struct starpu_vector_interface *)buffers[0]),STARPU_VECTOR_GET_NX( (struct starpu_vector_interface *)buffers[0]),((ROA_vector_scale *)_args)->factor
 );

 }


 void vector_scale (  float * arr, int size, float factor )
 {
 static ROA_vector_scale arg_vector_scale;

  arg_vector_scale.factor=factor;

 static struct_vector_scale * objSt_vector_scale = NULL;

 if( objSt_vector_scale == NULL)
 {
 objSt_vector_scale = ( struct_vector_scale *) malloc (sizeof( struct_vector_scale ));

 memset( &(objSt_vector_scale->cl_vector_scale), 0, sizeof(objSt_vector_scale->cl_vector_scale));

 objSt_vector_scale->cl_vector_scale_init = 0;
 }

 if(! objSt_vector_scale->cl_vector_scale_init ) // codelete initialization only once, at first invocation
 {
 objSt_vector_scale->cl_vector_scale.where =0|STARPU_CPU;

 objSt_vector_scale->cl_vector_scale.cpu_funcs[0]=scale_cpu_func_wrapper;
objSt_vector_scale->cl_vector_scale.cpu_funcs[1]=NULL;


  

  

 objSt_vector_scale->cl_vector_scale.nbuffers = 1;

  objSt_vector_scale->cl_vector_scale.modes[0] = STARPU_RW;




  



 objSt_vector_scale->cl_vector_scale_init = 1;
 }

  starpu_data_handle_t arr_handle;

  starpu_vector_data_register(  &arr_handle, 0, (uintptr_t)arr, size, sizeof(arr[0] ));



 {




 struct starpu_task *task = starpu_task_create();

 task->synchronous = 1;

 task->cl = &(objSt_vector_scale->cl_vector_scale);

  task->handles[0] = arr_handle;


 task->cl_arg = &arg_vector_scale;
 task->cl_arg_size = sizeof(ROA_vector_scale);

 /* execute the task on any eligible computational ressource */
 int ret = starpu_task_submit(task);

 if (ret == -ENODEV)
 {
 fprintf(stderr, "ERROR: No worker may execute this task\n");
 return;
 }

 }



  starpu_data_unregister(arr_handle);

  

 }


 #endif

