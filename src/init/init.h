#ifndef INIT
#define INIT

#include <EnvVar.h>
#include <methods.h>
//#include <config.h>


/** @defgroup group6 Initialization
@{  */

/** @brief check if number of arguments user inputs is within a valid range*/
void paramCheck(int num);

/** @brief read environment variable by name*/
void getEnv(std::string name, std::string &varS);

/** @brief read "CT_HOME" environmental variable, and copy it to EnvVar object's path field.*/
void setEnvPath(EnvVar *state);

/** @brief extract command-line arguments and set fields in EnvVar object. */
void parseEnvVar(EnvVar *env_, int argC,char **argV);


/** @brief encapsulate user input arguments into a global structure, EnvVar. This makes further checks easier. */
void sysInit(EnvVar *env_, int argC, char **argV);

/**  @brief Print info of initialization stage, used for verbose mode.*/
void initPrintInfo(EnvVar *env_);

/** @brief Sets the verbose level */
void setVerbose(EnvVar *env_, std::string value);

/**  @brief Print command line format, used when user input is not valid.*/
void usage();

/**  @brief Print file, such as XML schema, used for verbose mode. */
void printFile(std::string file);

/**	@} 
*/

#endif

