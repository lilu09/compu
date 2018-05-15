struct starpu_opencl_program * $SOPN2 = 0;
cl_kernel $CKN2 ;
cl_command_queue $CCQN2 ;

extern void $IMNO1 ( $IPL1 );

$TMTPST2
void $IMNWO1 (void *buffers[], void *_args)
{

	int id = starpu_worker_get_id();
	int devid = starpu_worker_get_devid(id);

	$SOLK2

	if (err != CL_SUCCESS) STARPU_OPENCL_REPORT_ERROR(err);

	/* peppher container declarations, if any */
 	$PCD1      
 	
	$IMNO1 (
	$PGBCL2
	);

	$CLF2

	$SORK2
}
