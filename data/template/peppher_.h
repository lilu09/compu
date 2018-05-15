#ifndef PEPPHER_H
#define PEPPHER_H

#include <starpu.h>
$INSTCL

#define USE_STARPU

//uint64_t PEPPHER_tagId=0;

#ifdef USE_STARPU
   #define PEPPHER_INITIALIZE() \
   struct starpu_conf conf; \
   starpu_conf_init(&conf); \
   $STCFOMP2 \
   int _ret_ = starpu_init(&conf); \
   STARPU_CHECK_RETURN_VALUE(_ret_, "starpu_init")
#else
   #define PEPPHER_INITIALIZE() 
#endif


#ifdef USE_STARPU
   #define PEPPHER_SHUTDOWN() \
   starpu_shutdown()
#else
   #define PEPPHER_SHUTDOWN()
#endif


// Include wrappers here for each interfaces which can have multiple implementations.
// Here, we only have one interface...
$INWQM2


#endif


