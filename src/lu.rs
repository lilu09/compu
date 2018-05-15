//filter header files
//".*from /usr/.*" = "";
//".*from .*" = "";
//"/usr/include/.*[0-9]:" = "";


//filter instantiation backtrace
//".*required from.*" = "";
//".*In instantiation of.*" = "";
//"/usr/include/.*[0-9]: " = "";
//".*from /usr/.*" = "";
//".*note: .*" = "";

"\.\./.*/" = "";
"include \"" = "include <";
"\.h\"$" = ".h>";
"\.hpp\"$" = ".hpp>";
"#include <../" = "#include <";

//Typedefs
//When your project uses general typedefs, 
//you might want to see your typedef'd name instead of the real type. 
