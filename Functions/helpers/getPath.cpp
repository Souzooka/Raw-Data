#include <libgen.h>
#include <cstring>
#include <string>

// returns path to a file from a path, e.g "path/to/file.fil" returns "path/to"
std::string getPath(std::string inputFilePath)
{
    char* cstr = new char [inputFilePath.length()+1];
    std::strcpy (cstr, inputFilePath.c_str());
    std::string path = dirname(cstr);
    delete[] cstr;
    cstr = 0;
    return path;
}
