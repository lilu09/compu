#ifndef ENTRYCOMPONENT_
#define ENTRYCOMPONENT_

#include <ComponentBase.h>
#include <Implementation.h>

/** @addtogroup group2
*
* @{
*/
/** @brief Component for application's entry, normally refers to main function */
class EntryComponent : public ComponentBase
{
	public:
		/** Parse entry component's XML file, and build Intermediate Representation for EntryComponent. */
		void parse(std::string fileName);
		
		/** Build intermediate representation of dependent component, if defaultValue is set to true, then for each type, the first added component will become the default component in the component configuration*/
		void buildIR(bool defaultValue);
        
		void handle_constraints_in_IR();

		//handle constraints at implementation level, usually at Component level, since 
		//it needs to modify component configuration, but for main() this is needed.
		void handle_entry_component_constraints();
		
		/** Print all necessary info of EntryComponent and dependent Components, used for verbose mode. */
		void printIR();
		
		/** Print an overview of Component dependency tree, used for verbose mode. */
		void printRelation();
		
		/** Print info of EntryComponent's dependent Components, used for verbose mode. */
		void printComponent();
		
		/** Print info of EntryComponent, used for verbose mode.*/
		void printMe();
		
		/** return target name that is used for makefile target.*/
		std::string getOutputName();
		
		/** reutrn true if atleast 1 OpenMP implementation exists in the program. */
		bool hasOpenMPImpl();
			
		/** Update link statement, since link statement can not be built until other compile statements has been added to Intermediate Representation. */
		void updateLinkStmt();
		
		/** generate header file "peppher.h"*/
		void generateHeader();
		
		/** generate makefile*/
		void generateMakefile();
		
		/** generate wrapper for every interface parsed*/
		void generateWrapper();

		/** EntryComponent's implementation. There should be only one Implementation in EntryComponent, normally main function, executed on CPU Platform. */
		Implementation *impl;
};

/** @} */

#endif

