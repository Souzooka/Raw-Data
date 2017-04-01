#include <fstream>
#include <string.h>

using namespace std;

// this function should be one of the two run when loading in a new file
// (the other being one that'll check if it's a RD or generic DAT)
// it takes in a file and checks the first four bytes to see if it is designated as a FAT file
// if true, then we know the header is actually inside the DAT file
// if false, then we need to search the directory for a .FAT file with the same name
// THIS DOES NOT DO FILE VALIDATION !!
bool isFatIncluded(std::ifstream &InputFile)
{
    char buffer[4];
    InputFile >> buffer;

    return !strcmp(buffer, "FAT");
}
