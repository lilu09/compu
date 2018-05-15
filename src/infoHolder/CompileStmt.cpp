#include <CompileStmt.h>
#include <methods.h>
#include <Element.h>
#include <helperFactory.h>
#include <Helper.h>


using namespace std;


/**  Default constructor, empty function. */
CompileStmt::CompileStmt(): validCompileStmt(true)
{  }

/**  Copy constructor.*/
CompileStmt::CompileStmt(CompileStmt *cmp):obj(cmp->obj),path(cmp->path),dep(cmp->dep),compiler(cmp->compiler),flag(cmp->flag),stmt(cmp->stmt),type(cmp->type), validCompileStmt(cmp->validCompileStmt)
{  }


/*!  
 * Constructor. This method initialize all member variables from syntax tree(tree). 
 * First argument(target) is position of Element which store a single compiling statement in syntax 
 * tree, since one syntax tree may contains several compile statements. 
 */
CompileStmt::CompileStmt(Node *target,Node *tree, string impPath)
{
	validCompileStmt = true; 
	
	//set obj
	setValue(obj,env.kb["OPT"],target);
	
	if(obj=="")
	{
		obj=trimSpaces(( (Element *)target)->attrs["name"]);
		if(obj=="")
		{
			error("Error in compileStmt: Name missing for one of the sourcefiles.");
		}
		removeSuffix(obj,'.');
		obj=obj+".o";
	}

	//set path
	Helper *helper=helperFactory::createHelper("PIFN1");
	string folder="";
	if(helper)
	{
		folder = trimSpaces(helper->getResult(tree));
		delete helper;
	}
	if(capitalizeString(folder)!="MAIN")
		path=impPath;
	else
		path="";

	//set dep
	dep=trimSpaces(( (Element *)target)->attrs["name"]);

	//set compiler
	setValue(compiler,env.kb["CMP"],target);

	//set type
	setValue(type,env.kb["CTP"],target);

	setValue(flag,env.kb["FLG"],target);
	flag = " $(CFLAGS) "+ flag;
	if(type=="")
		flag=flag+" -c";
	
	if(trimSpaces(compiler)=="" || capitalizeString(trimSpaces(compiler))=="NULL")
			validCompileStmt = false; // not a valid compile statement

	setStmt();
}


void CompileStmt::show()
{
	std::cerr<<"*** obj: "<<obj
			 <<", path: "<<path
			 <<", dep: "<<dep
			 <<", compiler: "<<compiler
			 <<", flag : "<<flag
			 <<", stmt : " << stmt
			 <<", type : "<<type
			 <<", validCompileStmt : "<<validCompileStmt<<"\n";
}

/*! 
 * Set member variable. Meta is path relative to target, and target is pointer to Element which store 
 * a single compile statement in syntax tree, since one syntax tree may contains several compile statements.
 */
void CompileStmt::setValue(string &var ,string meta, Node *tree)
{
	InfContainer *result=0;
	if(tree)
		result=fetchTree(meta,tree);
	if(result && !result->isEmpty() )
	{
		//cout<<"##exe"<<endl;
		var= trimSpaces(result->pop());
	}
	else
		var="";
}

/**  Set member variable stmt, which is complete compile command used in Makefile.*/
void CompileStmt::setStmt()
{
	stmt=obj+" : "+path+dep+" @ent @tab "+compiler+" "+path+dep+" "+flag+" -o "+obj+" @ent";
}

