

#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <algorithm>
#include <methods.h>
#include <error.h>
#include <SAXPrint.hpp>
#include <Element.h>
#include <Node.h>
#include <StringCouple.h>
#include <Component.h>
#include <iterator>

using namespace std;

class line : public std::string {};

std::istream &operator>>(std::istream &is, line &l)
{
    std::getline(is, l);
    return is;
}

/** @brief Load a set of space-separated string pairs  from a file to a map<string, string> structure. This method is useful for loading path infos of XML syntax tree. Used Actually for loading the knowledge file which contains one key value pari per line separated by space. */
void loadKeyValFileToMap(const string& fileName,map <string, string> *mapName)
{

	std::ifstream input_stream( fileName );

	std::istream_iterator<line> begin(input_stream), end;

	istringstream iss;
	string key, value;
	for (istream_iterator<line> it=begin; it!=end; ++it) {
		//for each line
		iss.clear();
		iss.str(*it);
		iss>>key;
		getline(iss, value);

		assertx(mapName->count(key)==0, "There should not be the same key existed in map before we try insert!");
		(*mapName)[key]=value;
	}

	mapName->erase("");

	
	//string line, key, value;
	//istringstream iss;
	//ifstream spec;
	//spec.open(fileName.c_str());
	//while(spec.good())
	//{
		//getline(spec,line);
		//iss.clear();
		//iss.str(line);
		//iss>>key;
		//getline(iss,value);

		//if(mapName->count(key)>0)
		   //{
			//string message="Key "+key+" already existed, you want to overwrite "+key+"?";
			//warn(message);
                    //}
		//mapName->insert( map<string, string>::value_type (key, value) );
	//}
	//mapName->erase("");
}


/** @brief Parse an XML file with validation to an syntax tree. Schema used for validation is stored in SOFTWARE_ROOT/data/schema directory. It is possible to specify a different XML schema by configuring Intermediate Representation (EnvVar). Called by EntryComponent and Component */
void buildComponentTree(string InfFileName, Node *&tree)
{	
	DEBUG_METHOD_ENTRY("buildComponentTree") // used for debugging purposes to trace problems...
	
	string fileName=InfFileName;
	string ns_sche=env.ns_schema;
	xmlparse(fileName,ns_sche,tree);
}


/** @brief Fetch a string from an XML syntax tree. The position specifying where to fetch from syntax tree is specified in meta as a string. An example of meta could be 'attribute@impPath peppher:component peppher:interface'. First word 'attribute@impPath' means the info is stored in the 'impPath' attribute of XML Element, whose path in XML syntax tree is rest of the string.  */
InfContainer *fetchTree(string meta_,Node *tree)
{
	DEBUG_METHOD_ENTRY("fetchTree") // used for debugging purposes to trace problems...
	
	InfContainer *result= new InfContainer();
	
	istringstream iss(meta_);
	string firstPart, secondPart;
	
	// to put first word e.g. attribute@name or content in firstPart and rest path to secondPart e.g. peppher:component peppher:interface
	iss>>firstPart;
	getline(iss,secondPart);

	Node *target=0;
    locate(tree,secondPart,target); // look for the secondPart, e.g., peppher:component peppher:interface

	if(target)
    {
		copyInf(firstPart,target,result); // search for attribute and meta e.g., attribute@name or content and put it to infContainer object "result"
		return result;

    }

   return 0;
}


/** @brief Locate target to a certain place of an XML syntax tree, according to given route.  This method is useful for fetching infos from XML syntax tree.*/
void locate(Node *tree,string route, Node *&target)
{

	istringstream iss(route);
	string bread;
	target=tree;
	if(route.size()==0)
	{
		assertx(0, "no route found");
		return;
	}
	while( iss.good() )
	{
		if(iss.peek()==13) 
			break;

		iss>>bread;

		if(target->existChild(bread) )
			target=target->getChild(bread);
		else
		{
			warn(bread+" do not exist in: " + route, REPORT_LEVEL_2);
			target=0;
			break;
		}
	}
}


/** @brief Copy infos into a container called InfContainer, given meta and located Element(target). Meta here is first word of path info, such as 'attribute@impPath'. This method should be called after locate method, which can offer located Element to this method. copyInf() serves as last step for fetching info from a syntax tree. */
void copyInf(string meta,Node *target,InfContainer *inf_)
{
	DEBUG_METHOD_ENTRY("copyInf") // used for debugging purposes to trace problems...
	
	string categ;
	decode(meta,categ,'@');
	string name;
	if(categ=="attribute")
	{
		decode(meta,name,'@');
		//just copy
		inf_->add( ((Element *)target)->attrs[name]);
	}
	else if(categ=="content")
	{
		inf_->add(((Element *)target)->content);
	}
	else
	{
		error("Attribute or content ("+name+") spells wrong");
	}
	
}


/** @brief Decode cuts the string and put first part in decode and remaining in meta. 
*  Cut string(meta) by delim, store rest in meta, and cut part in decode. This method is useful for processing syntax tree position info.*/
void decode(string &meta, string &decode, char delim)
{
	DEBUG_METHOD_ENTRY("decode") // used for debugging purposes to trace problems...
	
	istringstream iss(meta);
	char test[256];
	iss.getline(test,256,delim);
	decode=test;
	if(iss.good())
		getline(iss,meta);
	else
		meta="";
	
}

/** @brief Get the suffix of a string(var). The suffix is distinguished by delim. This method is useful for string calculation. */
void removeSuffix(string &var, char delim)
{
	DEBUG_METHOD_ENTRY("removeSuffix") // used for debugging purposes to trace problems...
	
//	istringstream iss(var);
//	ostringstream oss;
//	char c;
	
	var.erase( std::min( var.rfind(delim), var.size() ) );

//	while(iss.good())
//	{
//		iss>>c;
//		if(c==delim)
//		{
//			var=oss.str();
//			break;
//		}
//		oss<<c;
//	}
}

/** @brief Fetch a set of strings from an XML syntax tree. More details of parameter meta can be found in method fetchTree(). The method, for example, can be used for collecting all same attributes of children by specifying an root Element. */
InfContainer *fetchTreeIter(string meta_,Node *tree)
{

	InfContainer *result= new InfContainer();


	istringstream iss(meta_);
	string meta, route;
	iss>>meta;
	getline(iss,route);

	//std::cout<<meta<<std::endl;
	//std::cout<<route<<std::endl;

	Node *target=0;
	locate(tree,route,target);

	if(target)
	{

		copyInfIter(meta,target,result);
		return result;

	}

	return 0;
}

/** @brief Similar to copyInf, but this method can copy a set of strings from children of Element(target).*/
void copyInfIter(string meta,Node *target,InfContainer *inf_)
{
	DEBUG_METHOD_ENTRY("copyInfIter") // used for debugging purposes to trace problems...
	
	if(target==0)
		return;
	string categ;
	decode(meta,categ,'@');
	if(categ=="attribute")
	{
		string name;
		decode(meta,name,'@');
		
		auto size=target->child.size();
		for(decltype(size) i=0;i<size;++i)
			inf_->add( ((Element *)target->child[i])->attrs[name] );
	    
	}
	else if(categ=="content")
	{
		warn("Warning: In methods.c (copyInfIter): Content category is found");
	}
	else
	{
		error("attribute or content spells wrong");
	}
	
}


/** @brief Fetch a set of string pairs from an XML syntax tree. More details of parameter meta can be found in method fetchTree(). This method could be an effective supplement for method fetchTreeIter. For example, if a set of string pairs is needed, fetchTreeIter can be called twice and get two sets of strings instead of a set of string pair. However, it is not possible to distinguish which strings in two sets of strings come from same child Element. To overcome this problem, method fetchTreeIterTwo() should be used since string pair shows such information.*/
InfContainer *fetchTreeIterTwo(string meta_,Node *tree)
{

	InfContainer *result= new InfContainer();

	istringstream iss(meta_);
	string firstPart, secondPart;
	iss>>firstPart;
	getline(iss,secondPart);

	Node *target;
	locate(tree,secondPart,target);

	if(target)
	{
		copyInfIterTwo(firstPart,target,result);
		return result;
	}

	return 0;
}

void fetchTreeIterTwo2(const string& meta, Node *tree, InfContainer2 &result)
{
	istringstream iss(meta);
	string dsl, route;
	iss>>dsl;
	getline(iss, route);

	Node *target=0;
	locate(tree, route, target);

	if(target)
		copyInf2IterTwo(dsl, target, result);

}

void copyInf2IterTwo(string dsl, Node const * const target, InfContainer2 &result)
{
	string categ;
	decode(dsl, categ, '@');
	string name1, name2, value1, value2;

	if(categ == "attribute") {
		decode(dsl, name1, '@');
		decode(dsl, name2, '@');
		auto size=target->child.size();
		for(decltype(size) i=0;i<size;++i)
		{
			value1=((Element *)target->child[i])->attrs[name1];
			value2=((Element *)target->child[i])->attrs[name2];
			result.inf.push_back(value1);
			result.inf2.push_back(value2);
		}

	}else if(categ == "content"){
		assertx(0, "content not develped in copyInf2IterTwo, please do that!");
	}else{
		assertx(0, "Spell error, should be attribute or content");
	}
}


/** @brief Similar to copyInfIter, but this method can copy a set of string pairs. The difference between this method and copyInfIter is similar to the difference described in fetchTreeIterTwo.*/
void copyInfIterTwo(string meta,Node *target,InfContainer *inf_)
{
	DEBUG_METHOD_ENTRY("copyInfIterTwo") // used for debugging purposes to trace problems...
	
	string categ;
	decode(meta,categ,'@');
	string name1,name2;
	
	if(categ=="attribute")
	{	
		decode(meta,name1,'@');
		decode(meta,name2,'@');

		//iterate and copy	
		auto size=target->child.size();
		for(decltype(size) i=0;i<size;++i)
		{
			 string va=((Element *)target->child[i])->attrs[name1] +" "+ ((Element *)target->child[i])->attrs[name2];
			 inf_->add( va);	 
		}
	}
	else if(categ=="content")
	{
		warn("Warning: In methods.c (copyInfIterTwo): Content category is found");
	}
	else
	{
		error("Attribute or content("+name1+" and/or "+name2+ ") spells wrong");
	}
}




/** @brief Get all the filenames under a certain directory. This method is useful for detecting all xml files given the directory where implementations locate so that parsing can continue from entry xml file.*/
int getFilesListFromDir(string dir, vector<string> &files)
{
	DEBUG_METHOD_ENTRY("getdir") // used for debugging purposes to trace problems...
	
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

/** @brief Get the suffix of a string(var). The suffix is distinguished by delim. This method is useful for string calculation. */
string getSuffix(string var, char delim)
{
	DEBUG_METHOD_ENTRY("getSuffix") // used for debugging purposes to trace problems...
	
	istringstream iss(var);
	ostringstream oss;
	char c;
	int flag=0;

	while(iss.good())
	{
		if(iss.peek()==13||iss.peek()==-1)
			break;
		iss>>c;
		if(c==delim)
		{
			flag=1;
			continue;
		}
		if(flag==1)
			oss<<c;
	}
	return oss.str();
}


/** @brief Load a set of variables from a file to a map<string, string> structure. In files, variables are distinguished by starting character, which is specified by delim. By default, '$' is used, but for makefile generation, '$' has a special meaning so a different delim may be specified in that case. This method, for example, can be used to get all variables from a template file.*/
void loadVarToMap(string infile,map <string, string> *mapName,char delim)
{
	DEBUG_METHOD_ENTRY("loadVarToMap") // used for debugging purposes to trace problems...
	
   string line,word;
   ifstream is;
   is.open(infile.c_str());
   
   if ( is.is_open() )
   {
	while(is.good())
	  {
		getline(is,line);
		istringstream iss(line);
		
		while(iss.good())
		 {
			word="";
			if(iss.peek()==13)
				break;
			iss>>word;
			
			removeFirstCharacterIfDelimElseEmptyString(word,delim);
			if(word!="")
				(*mapName)[word]="null";
		}
	}
  }
  is.close();
}


/** @brief Remove first character of a string if the first character is equal to delim, otherwise it will set value to null. This method is useful for checking whether a string is a variable or not since every variable start with a special character, such as '$'.*/
void removeFirstCharacterIfDelimElseEmptyString(string &value,char delim)
{
	DEBUG_METHOD_ENTRY("removeFirstCharacterIfDelimElseEmptyString") // used for debugging purposes to trace problems...
	
	istringstream iss(value);
	char c;
	iss>>c;
	if(c==delim)
	{
		string newValue;
		getline(iss,newValue);
		value=newValue;
	}
	else
		value="";
}

/** @brief Calcuate values of variables given an Intermediate Representation Component. Variables with empty values are stored in source, and those with calculated values in dest after function returns. This method is useful for generating header and wrapper files for StarPU Platform.*/
void updateVariable(map <string, string> *source, map <string, string> *dest, Component *com)
{
	DEBUG_METHOD_ENTRY("updateVariable") // used for debugging purposes to trace problems...
	
		StringCouple *curr=0;
		while( source->size()>0 )
		{
			popMap(source,curr);
			curr->change(com);
			addPool(dest,curr);
		}
}


/** @brief Calcuate values of variables given an Intermediate Representation EntryComponent. The variables with empty values are stored in source, and those with calculated values in dest after function returns. This method is useful for generating Makefile since all components information should be available. If EntryComponent is given, then traversing through all components is possible.*/
void updateVariable(map <string, string> *source, map <string, string> *dest, EntryComponent *com)
{
	DEBUG_METHOD_ENTRY("updateVariable(EntryComponent)") // used for debugging purposes to trace problems...
	
		StringCouple *curr=0;
		while( source->size()>0 )
		{
			popMap(source,curr);
			curr->change(com);
			addPool(dest,curr);
		}
}


/** @brief Pop one string pair from source, and store it as a StringCouple structure. This method is useful to traverse a map <string, string> when calculating variables.
* StringCoulple is a helper class containing key, value pair and method to generate key value based on helpers for Component/EntryComponent */
void popMap(map <string, string> *source,StringCouple *&curr)
{
	DEBUG_METHOD_ENTRY("popMap") // used for debugging purposes to trace problems...
	curr=0;
	if( existUnit(source) )
	{
		map <string, string>::const_iterator first_ = source->begin();
		curr= new StringCouple(first_->first,first_->second);
		source->erase(first_->first);
	}
}


/** @brief Check if there is some pair stored in map <string, string>. This method erases empty keys in map <string, string>, so that only valid pairs are considered.*/
bool existUnit(map <string, string> *pol)
{
	DEBUG_METHOD_ENTRY("existUnit") // used for debugging purposes to trace problems...
	
	pol->erase("");
    return !pol->empty();
}


/** @brief Add a StringCouple structure to map <string, string>, and perform type conversion. */
void addPool(map <string, string> *pol,StringCouple *curr)
{
	DEBUG_METHOD_ENTRY("addPool") // used for debugging purposes to trace problems...
	
	addPool(pol,curr->key,curr->value);
}


/** @brief Add a key-value pair to map <string, string>, and perform type conversion. */
void addPool(map <string, string> *pol,string key, string value)
{
	DEBUG_METHOD_ENTRY("addPool(map <string, string>, string, string)") // used for debugging purposes to trace problems...
	
	if(pol->count(key)>0)
	{
		if((*pol)[key] != value)
		{
			string message="Key "+key+" already existed, will overwrite, old: "+(*pol)[key]+", new: "+value +".";
			warn(message);
		}
	}
	pol->insert( map<string, string>::value_type (key, value) );
}


/** @brief Replace infile's variables with values, using variable-value pair stored in pool. After replacement, outFile is generated. This method is mainly used for header and wrapper generation.*/
void replaceWithVariablesValue(string infile, string outfile, map <string, string> *pool, char delim)
{
	DEBUG_METHOD_ENTRY("replace(string, string, map <string, string>, char)") // used for debugging purposes to trace problems...
	
    string line,word;
    ifstream is;
    ofstream os;
    is.open(infile.c_str());
    os.open(outfile.c_str());
   

   if ( is.is_open()  && os.is_open() )
   {
	  while(is.good())
	  {
		getline(is,line);
		istringstream iss(line);
		os<<endl;
		while(iss.good())
		 {
			word="";
			if(iss.peek()==13)
				break;
			iss>>word;
			recover(word,pool, delim); // will use work key with delim to check for the value in the pool
			if(!word.empty())
				os<<' '<<word;
		}
	  }
   }
   else
   {
   	error("Error while opening files"+ infile + "  and/or "+outfile);
   }
 
  is.close();
  os.close();
}


/** @brief Replace delim with enter in infile, and store the result in outfile. If no outfile exists, a new file will be generated. This method is useful for header generation when several statements are in one line and syntactically unvalid.*/
void replaceWithEnterKey(string infile, string outfile, string delim)
{
	DEBUG_METHOD_ENTRY("replace(string, string, string)") // used for debugging purposes to trace problems...
	
    string line,word;
    ifstream is;
    ofstream os;
    is.open(infile.c_str());
    os.open(outfile.c_str());

    if ( is.is_open()  && os.is_open() )
    {
	  while(is.good())
	  {
		getline(is,line);
		istringstream iss(line);
		os<<endl;
		while(iss.good())
		 {
			word="";
			if(iss.peek()==13)
				break;
			iss>>word;
			
			if(word==delim)
				os<<endl;
			else if(!word.empty())
				os<<' '<<word;
		}
	  }
   }
   is.close();
   os.close();
}


/** @brief Look up value of key in map <string, string>. Key should start with delim, otherwise fetch will not succeed. This method is mainly used for preparation of replacement of template file. */
void recover(string &key, map <string, string> *pool,char delim)
{
	DEBUG_METHOD_ENTRY("recover") // used for debugging purposes to trace problems...
	
	istringstream iss(key);
	char c;
	iss>>c;
	if(c==delim)
	{
		string name, newKey;
		iss>>name;
		newKey=(*pool)[name];
		if(newKey=="")
			warn(name+" do not exist", REPORT_LEVEL_3);
		key=newKey;
	}
//	else
//		warn("cannot fecth the "+ key + " as it does not start with char " + delim);
}


/** @brief Merge two files together, and store result to dest. This method is useful for wrapper generation where several part are generated separately and merged together.*/
void mergeFile(string dest, string src)
{
	DEBUG_METHOD_ENTRY("mergeFile") // used for debugging purposes to trace problems...
	
	fstream a,b;
	
	a.open(dest.c_str());
	a.seekg (0, ios::end);
	
	b.open(src.c_str());
	string line;
	while(b.good())
	{
		getline(b,line);
		a<<endl<<line;
	}

	a.close();
	b.close();

	remove(src.c_str());
}

/** @brief Print all string pairs in a map, with a header shown on top. This method is useful for verbose mode.*/
void showMap(map<string, string> *pool, string header)
{
	DEBUG_METHOD_ENTRY("showMap") // used for debugging purposes to trace problems...
	
	cout<<endl<<"/****************************************/"<<endl;
	cout<<header<<": "<<endl;
	map<string, string>::iterator it;
	for(it=pool->begin();it!=pool->end();it++)
	{
		cout<<"variable: "<<it->first<<"      "<<"value: "<<it->second<<endl;
	}
	cout<<"/****************************************/"<<endl<<endl;
}


/** @brief Replace infile for the following rules, '@ent' with an enter and '@tab' with a tab. This method is useful for Makefile generation where special characters are required, such that a Tab is required before a compile command. */
void replaceWithEnterTabKey(string infile, string outfile)
{
	DEBUG_METHOD_ENTRY("replace(string, string)") // used for debugging purposes to trace problems...
	
   string line,word;
   ifstream is;
   ofstream os;
   is.open(infile.c_str());
   os.open(outfile.c_str());

   if ( is.is_open()  && os.is_open() )
  {
	while(is.good())
	  {
		getline(is,line);
		istringstream iss(line);
		os<<endl;
		while(iss.good())
		 {
			word="";
			if(iss.peek()==13)break;
			iss>>word;
			
			if(word=="@ent")
				os<<endl;
			else if(word=="@tab")
				os<<(char)9;
			else
			os<<word<<' ';
		}
	}
  }
  is.close();
  os.close();
}


/** @brief Delete spaces if there is any at the start or end of a string, used for string calculation.*/
const std::string trimSpaces(const std::string& pString,
                       const std::string& pWhitespace)
{
	DEBUG_METHOD_ENTRY("trimSpaces") // used for debugging purposes to trace problems...
	
    const size_t beginStr = pString.find_first_not_of(pWhitespace);
    if (beginStr == std::string::npos)
    {
        // no content
        return "";
    }

    const size_t endStr = pString.find_last_not_of(pWhitespace);
    const size_t range = endStr - beginStr + 1;

    return pString.substr(beginStr, range);
}


//typedef std::string::value_type char_t;

string::value_type up_char( string::value_type ch )
{
    return std::use_facet< std::ctype< string::value_type > >( std::locale() ).toupper( ch );
}

string::value_type lower_char( string::value_type ch )
{
    return std::use_facet< std::ctype< string::value_type > >( std::locale() ).tolower( ch );
}

/** @brief To Capitalize (a-z to A-Z) the string */
string capitalizeString(const string &src)
{
	std::string result;
    std::transform( src.begin(), src.end(), std::back_inserter( result ), up_char );
    return result;
}


/** @brief To Capitalize (a-z to A-Z) the string */
string unCapitalizeString(const string &src)
{
	std::string result;
    std::transform( src.begin(), src.end(), std::back_inserter( result ), lower_char );
    return result;
}

bool containString(const std::string &str, const std::string &findStr)
{
	size_t found = str.find(findStr);
	return (found!=string::npos);
}

string convertIntToString(int val)
{
	ostringstream convert;
	convert << val;
	return convert.str(); 
}




