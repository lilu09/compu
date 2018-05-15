#ifndef METHODS_
#define METHODS_

#include <string>
#include <error.h>
#include <types.h>
#include <Node.h>
#include <EnvVar.h>
#include <StringCouple.h>
#include <iostream>


extern EnvVar env;


class Component;

/** @defgroup group3 Library
@{  */



/** @brief Load a set of std::string pairs from a file to a map<std::string, std::string> structure. This method is useful for loading path infos of XML syntax tree. */
void loadKeyValFileToMap(const std::string& fileName,std::map <std::string, std::string> *mapName);

/** @brief Load a set of variables from a file to a map<std::string, std::string> structure. In files, variables are distinguished by starting character, which is specified by delim. By default, '$' is used, but for makefile generation, '$' has a special meaning so a different delim may be specified in that case. This method, for example, can be used to get all variables from a template file.*/
void loadVarToMap(std::string infile,std::map <std::string, std::string> *mapName,char delim='$');

/** @brief Parse an XML file with validation to an syntax tree. Schema used for validation is stored in SOFTWARE_ROOT/data/schema directory. It is possible to specify a different XML schema by configuring Intermediate Representation (EnvVar).*/
void buildComponentTree(std::string InfFileName, Node *&tree);

/** @brief Fetch a std::string from an XML syntax tree. The position specifying where to fetch from syntax tree is specified in meta as a string. An example of meta could be 'attribute@impPath peppher:component peppher:interface'. First word 'attribute@impPath' means the info is stored in the 'impPath' attribute of XML Element, whose path in XML syntax tree is rest of the string.  */
InfContainer *fetchTree(std::string meta,Node *tree);

/** @brief Fetch a set of strings from an XML syntax tree. More details of parameter meta can be found in method fetchTree(). The method, for example, can be used for collecting all same attributes of children by specifying an root Element. */
InfContainer *fetchTreeIter(std::string meta,Node *tree);

/** @brief Fetch a set of std::string pairs from an XML syntax tree. More details of parameter meta can be found in method fetchTree(). This method could be an effective supplement for method fetchTreeIter. For example, if a set of std::string pairs is needed, fetchTreeIter can be called twice and get two sets of strings instead of a set of std::string pair. However, it is not possible to distinguish which strings in two sets of strings come from same child Element. To overcome this problem, method fetchTreeIterTwo() should be used since std::string pair shows such information.*/
InfContainer *fetchTreeIterTwo(std::string meta,Node *tree);
void fetchTreeIterTwo2(const std::string& meta, Node *tree, InfContainer2 &result);

/** @brief Locate target to a certain place of an XML syntax tree, according to given route.  This method is useful for fetching infos from XML syntax tree.*/
void locate(Node *tree,std::string route, Node *&target);

/** @brief Copy infos into a container called InfContainer, given meta and located Element(target). Meta here is first word of path info, such as 'attribute@impPath'. This method should be called after locate method, which can offer located Element to this method. copyInf() serves as last step for fetching info from a syntax tree. */
void copyInf(std::string meta,Node *target,InfContainer *inf);

/** @brief Similar to copyInf, but this method can copy a set of strings from children of Element(target).*/
void copyInfIter(std::string meta,Node *target,InfContainer *inf_);

/** @brief Similar to copyInfIter, but this method can copy a set of std::string pairs. The difference between this method and copyInfIter is similar to the difference described in fetchTreeIterTwo.*/
void copyInfIterTwo(std::string meta,Node *target,InfContainer *inf_);
void copyInf2IterTwo(std::string dsl, Node const * const target, InfContainer2 &result);


/** @brief Cut string(meta) by delim, store rest in meta, and cut part in decode. This method is useful for processing syntax tree position info.*/
void decode(std::string &meta, std::string &decode, char delim);

/** @brief Get the suffix of a string(var). The suffix is distinguished by delim. This method is useful for std::string calculation. */
std::string getSuffix(std::string var, char delim);

/** @brief Remove the suffix of a string(var). The suffix is distinguished by delim. This method is useful for std::string calculation*/
void removeSuffix(std::string &var, char delim);

/** @brief Remove first character of a std::string if the first character is equal to delim, otherwise it will set value to null. This method is useful for checking whether a std::string is a variable or not since every variable start with a special character, such as '$'.*/
void removeFirstCharacterIfDelimElseEmptyString(std::string &value,char delim);

/** @brief Get all the file names under a certain directory. This method is useful for detecting all xml files given the directory where implementations locate so that parsing can continue from entry xml file.*/
int getFilesListFromDir (std::string dir,  std::vector<std::string> &files);

/** @brief Calcuate values of variables given an Intermediate Representation Component. Variables with empty values are stored in source, and those with calculated values in dest after function returns. This method is useful for generating header and wrapper files for StarPU Platform.*/
void updateVariable(std::map <std::string, std::string> *source, std::map <std::string, std::string> *dest, Component *com);

/** @brief Calcuate values of variables given an Intermediate Representation EntryComponent. The variables with empty values are stored in source, and those with calculated values in dest after function returns. This method is useful for generating Makefile since all components information should be available. If EntryComponent is given, then traversing through all components is possible.*/
void updateVariable(std::map <std::string, std::string> *source, std::map <std::string, std::string> *dest, EntryComponent *com);

/** @brief Pop one std::string pair from source, and store it as a StringCouple structure. This method is useful to traverse a std::map <std::string, std::string> when calculating variables.*/
void popMap(std::map <std::string, std::string> *source,StringCouple *&curr);

/** @brief Check if there is some pair stored in std::map <std::string, std::string>. This method erases empty keys in std::map <std::string, std::string>, so that only valid pairs are considered.*/
bool existUnit(std::map <std::string, std::string> *pol);

/** @brief Add a StringCouple structure to std::map <std::string, std::string>, and perform type conversion. */
void addPool(std::map <std::string, std::string> *pol,StringCouple *curr);

/** @brief Add a key-value pair to std::map <std::string, std::string>, and perform type conversion. */
void addPool(std::map <std::string, std::string> *pol,std::string key, std::string value);

/** @brief Replace infile's variables with values, using variable-value pair stored in pool. After replacement, outFile is generated. This method is mainly used for header and wrapper generation.*/
void replaceWithVariablesValue(std::string infile, std::string outfile, std::map <std::string, std::string> *pool, char delim='$');

/** @brief Replace delim with enter in infile, and store the result in outfile. If no outfile exists, a new file will be generated. This method is useful for header generation when several statements are in one line and syntactically unvalid.*/
void replaceWithEnterKey(std::string infile, std::string outfile, std::string delim);

/** @brief Replace infile for the following rules, '@ent' with an enter and '@tab' with a tab. This method is useful for Makefile generation where special characters are required, such that a Tab is required before a compile command. */
void replaceWithEnterTabKey(std::string infile, std::string outfile);

/** @brief Look up value of key in std::map <std::string, std::string>. Key should start with delim, otherwise fetch will not succeed. This method is mainly used for preparation of replacement of template file. */
void recover(std::string &key, std::map <std::string, std::string> *pool, char delim='$');

/** @brief Merge two files together, and store result to dest. This method is useful for wrapper generation where several part are generated separately and merged together.*/
void mergeFile(std::string dest, std::string src);

/** @brief Print all std::string pairs in a map, with a header shown on top. This method is useful for verbose mode.*/
void showMap(std::map<std::string, std::string> *pool, std::string header);

/** @brief Delete spaces if there is any at the start or end of a string, used for std::string calculation.*/
const std::string trimSpaces(const std::string& pString, const std::string& pWhitespace = " \t");

/** @brief To Capitalize the std::string */
std::string capitalizeString(const std::string &value);

/** @brief To Un-Capitalize the std::string */
std::string unCapitalizeString(const std::string &value);


/** @brief check whether the string contains a substring */
bool containString(const std::string &str, const std::string &findStr);

/** @brief converts integer to string */
std::string convertIntToString(int val);


template <class T>
bool from_string(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}


#ifdef NDEBUG
#define assertx(cond, message) 
#else
#define assertx(cond, message) \
	if(!(cond)) { \
		std::cerr <<__FILE__<<":"<<__LINE__<<": assertion "<<#cond<<" failed: "<<message<<"."<<std::endl; \
		exit(1); \
	}
#endif




/** @brief used to read file line by line by iterator */
class line;

std::istream &operator>>(std::istream &is, line &l);

/** @} */
#endif

