#ifndef ERROR_
#define ERROR_

#include <string>
//#include <config.h>

enum REPORT_LEVEL{REPORT_LEVEL_1,REPORT_LEVEL_2, REPORT_LEVEL_3};

/** @defgroup group4 Error handling
@{  */
/** @brief  Fatal error, message is shown and program terminated. This method is useful for serious error handling.*/
void fatal(std::string message);

/** @brief  Error, message is shown and program terminated. This method is useful for normal error handling. */
void error(std::string message);

/** @brief  Warning, message is shown and program continued. This method is useful for minor error or perspective error handling. */
void warn(std::string message, REPORT_LEVEL rl = REPORT_LEVEL_1);

/**	@} 
*/

//#define DEBUG_LEVEL 3

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL 0
#endif

#if DEBUG_LEVEL > 0
#include <iostream>
#endif

#if DEBUG_LEVEL > 0
    #define DEBUG_LEVEL_1(msg) std::cerr<<"* Level 1: "<<msg<<"\n";
#else
	#define DEBUG_LEVEL_1(msg) 
#endif

#if DEBUG_LEVEL > 1
    #define DEBUG_LEVEL_2(msg) std::cerr<<"* Level 2: "<<msg<<"\n";
#else
	#define DEBUG_LEVEL_2(msg) 
#endif

#if DEBUG_LEVEL > 2
    #define DEBUG_LEVEL_3(msg) std::cerr<<"* Level 3: "<<msg<<"\n";
    #define DEBUG_METHOD_ENTRY(msg) std::cerr<< __FILE__ <<", line "<< __LINE__ << ": "<< msg <<"\n";
#else
	#define DEBUG_LEVEL_3(msg) 
	#define DEBUG_METHOD_ENTRY(msg)
#endif








#endif

