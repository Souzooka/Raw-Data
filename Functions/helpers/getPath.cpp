#include <libgen.h>
#include <cstring>
#include <string>

using namespace std;

// returns path to a file from a path, e.g "path/to/file.fil" returns "path/to"
string getPath(string inputFilePath)
{
    char* cstr = new char [inputFilePath.length()+1];
    strcpy (cstr, inputFilePath.c_str());
    string path = dirname(cstr);
    delete[] cstr;
    cstr = 0;
    return path;
}
