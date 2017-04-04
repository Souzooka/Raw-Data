#include <libgen.h>
#include <cstring>
#include <string>

// returns file name from a path, e.g "path/to/file.fil" returns "file.fil"
std::string getFileNameFromPath(std::string inputFilePath)
{
    char* cstr = new char [inputFilePath.length()+1];
    std::strcpy (cstr, inputFilePath.c_str());
    std::string fileName = basename(cstr);
    delete[] cstr;
    cstr = 0;
    return fileName;
}
