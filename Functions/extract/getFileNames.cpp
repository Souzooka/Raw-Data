#include <inttypes.h>
#include <fstream>
#include "../../helpers.h"

using namespace std;

// This function returns an array of strings of file names in a .FAT file.
// All strings are null-terminated.
string* getFileNames(ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    uint32_t* namePtrs = getFileNamePtrs(inputFile);
    string* fileNames = new string[iterations];

    uint32_t currentPtr;

    for (uint32_t i = 0; i < iterations; ++i)
    {
        currentPtr = namePtrs[i];
        inputFile.seekg(currentPtr);
        getline(inputFile, fileNames[i], '\0');
    }

    return fileNames;
}
