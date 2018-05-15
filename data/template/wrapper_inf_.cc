$TMTPST2
void $IN1 ( $IPL1 )
{
  $ROCNR3
  
  $ROAA2
  
  static $SCLB3 * $SCLBO2 = NULL;
  
  if( $SCLBO2 == NULL)
  {
  	$SCLBO2 = ( $SCLB3 *) malloc (sizeof( $SCLB3 ));
  	
  	$SCLBMS2
  	
  	$SCLBI2
  }
  
  if(! $CLNB3 ) // codelete initialization only once, at first invocation
  {
	  $CLRL2
	
	  $CCCS2
	
	  $CUCC2
	  
	  $OPCC2
	
	  $CLBN2
	  
	  $CLMS2	  
	  
	  $HBPMA2
	
	  $LCLSC2
	  
	  $OMPFJM2
	  
	  $CLNB3 = 1;
  }

  $HD2

  $DRS2

  $STCL2
  {
  	$ROCNR4
  	
  	$ROAA3
  	
  struct starpu_task *task = starpu_task_create();
  
  $TASKSYNC

  $CLTB2

  $THBS2

  $ROATA2
  $ROATSA2

  /* execute the task on any eligible computational ressource */
  int ret = starpu_task_submit(task);

  if (ret == -ENODEV)
  {
      fprintf(stderr, "ERROR: No worker may execute this task\n");
      return;
  }
  
  }

	$TWFA
	
    $URDS2

	$SOU2

}


#endif

