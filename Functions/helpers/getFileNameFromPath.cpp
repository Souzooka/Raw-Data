#include <cstring>
#include <string>

using namespace std;

// returns file name from a path, e.g "path/to/file.fil" returns "file.fil"
string getFileNameFromPath(string inputFilePath)
{
    char* cstr = new char [inputFilePath.length()+1];
    strcpy (cstr, inputFilePath.c_str());
    string fileName = basename(cstr);
    delete[] cstr;
    cstr = 0;
    return fileName;
}
