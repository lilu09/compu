#ifndef TPLT_
#define TPLT_

#include <Helper.h>
#include <string>


/** @addtogroup group5

  @{
*/

/** @brief Template sign.
*  @details This class is responsible for generating template sign, for example: 'template' if ' type="template" ' is contained in XML file of  implementation type. */
class TPLT : public Helper
{
	public:
		/** Calculate variable TPLT from Syntax tree.Calculated variable TPLT is used for building Intermediate Representation.*/
	    std::string getResult(Node *tree);
};
/**	@} 
*/
#endif

