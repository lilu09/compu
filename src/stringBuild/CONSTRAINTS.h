#ifndef STATIC_CONSTRAINT_
#define STATIC_CONSTRAINT_

#include <string>
#include <vector>
#include <Helper.h>
#include <Node.h>
#include <Component.h>
#include <iostream>
#include <iterator>
#include <InfContainer.h>
#include <methods.h>
#include <ComConfig.h>
#include <assert.h>
#include <Constraints.h>

/** @addtogroup group5

  @{
  */

/** @brief  
 *  @details 
 */
class CONSTRAINTS : public Helper
{
	public:
		/** */
		Constraints get_result(Component *com) override final
		{
			return Constraints();
		}
		/** */
		Constraints get_result(Node *tree) override final
		{

			//InfContainer *srcName=fetchTreeIter(env.kb["STATIC_CONSTRAINT"],tree);
			//vector<string> empty_vector;
			//if(srcName==0) return empty_vector;  //maybe there is no contraints defined, thus return an empty vector

			//string curr="", tmp;
			//stringstream iss;
			//char c;
			//int size=srcName->inf.size();
			//return srcName->inf;
			
			InfContainer2 tree_result;
			fetchTreeIterTwo2(env.kb["CONSTRAINTS"], tree, tree_result);

			Constraints constraints;
			auto size=tree_result.inf.size();
			for(decltype(size) i=0; i< size; ++i)
			{
				if( tree_result.inf[i] == "static" )
					constraints.add( new Static_Constraint( tree_result.inf2[i])  );
				else if( tree_result.inf[i] == "dynamic" )
					constraints.add( new Dynamic_Constraint( tree_result.inf2[i])  );
				else
					assertx(0, "spell error.");

			}

			//constraints.print_me();


			//std::copy(tree_result.inf.begin(), tree_result.inf.end(), std::ostream_iterator<string>(std::cout, " ") );
			//std::cout<<std::endl;
			//std::copy(tree_result.inf2.begin(), tree_result.inf2.end(), std::ostream_iterator<string>(std::cout, " ") );
			//std::cout<<std::endl;
			


			return constraints;
		}
};
/**	@} 
*/












#endif

