#ifndef SN1_
#define SN1_

#include <Helper.h>
#include <string>

/** @addtogroup group5

  @{
*/

/** @brief Source file name.
*  @details This class is responsible for generating Source file name, for example: 'vector_scal_cpu.c', this info is used for makefile generation.
*/

class SN1 : public Helper
{
	public:
		/** Calculate variable SN1 from Syntax tree.Calculated variable SN1 is used for building Intermediate Representation.*/
		std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

