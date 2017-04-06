#include <fstream>
#include <inttypes.h>
#include "../../helpers.h"

using namespace std;

// this function should be one of the two run when loading in a new file
// (the other being one that'll check if it's a RD or generic DAT)
// it returns a value based on if there is a .FAT file with the same name in the directory.
// THIS DOES NOT DO FILE VALIDATION !!
bool isFatIncluded(string inputFilePath)
{
    string basePath = getPath(inputFilePath);
    string fileName = getFileNameFromPath(inputFilePath);
    string fileToCheck = basePath + "/" + fileName.substr(0, fileName.length() - 4) + ".FAT";

    ifstream infile(fileToCheck.c_str());
    return !infile.good();


}
