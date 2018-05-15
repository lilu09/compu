#ifndef INFCONTAINER_
#define INFCONTAINER_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <InfContainer.h>


/** @addtogroup group2
 *
 * @{
 */
/** @brief  An container for storing a set of strings. This class is useful to store all kinds of results from std::string calculation. It stoed them in a vector<string> and can do some simple operations such as concat all std::string with a delim character etc. */
class InfContainer
{
	public:
		/**  Check if this container is empty. */
		bool isEmpty(){return (inf.size()==0);}
		/**  Pop one std::string from this container. */
		std::string pop() { 
/*{{{*/
			if(!isEmpty())
			{
				std::vector<std::string>::iterator iter;
				iter = inf.begin();
				std::string result=(*iter);
				inf.erase(iter);
				return result;
			} 
			return "";
/*}}}*/
		}

		/**  Add one std::string to this container. */
		void add(std::string value)
		{
/*{{{*/
			inf.push_back(value);
/*}}}*/
		}

		/**  Converge all strings in this container to one string, using delim to connect them.*/
		std::string converge(std::string delim)
		{
/*{{{*/
			std::string result=" ";
			if(!inf.empty())
				result=pop();
			while(!inf.empty())
				result+=delim+pop();
			return result;
/*}}}*/
		}

		/**  Container for strings. */
		std::vector<std::string> inf;

};

/** @brief allow to have two vectors of string, easier for fetthTreeIterTwo */
class InfContainer2 : public InfContainer
{
	public: 
		std::vector<std::string> inf2;
};

/** @} */


#endif







