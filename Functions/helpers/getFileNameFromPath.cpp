#include <libgen.h>
#include <cstring>
#include <string>

std::string getFileNameFromPath(std::string inputFilePath)
{
    char* cstr = new char [inputFilePath.length()+1];
    std::strcpy (cstr, inputFilePath.c_str());
    std::string fileName = basename(cstr);
    delete[] cstr;
    cstr = 0;
    return fileName;
}
