#include <fstream>
#include <string.h>
#include <inttypes.h>

using namespace std;

// this function should be one of the two run when loading in a new file
// (the other being one that'll check if it's a RD or generic DAT)
// it takes in a file and checks the first four bytes to see if it is designated as a FAT file
// if true, then we know the header is actually inside the DAT file
// if false, then we need to search the directory for a .FAT file with the same name
// THIS DOES NOT DO FILE VALIDATION !!
bool isFatIncluded(std::ifstream &inputFile)
{
    // the really big ROOT file caused a segmentation fault, in this function of all things, while other big ones like STR do not,
    // so here's a lazy but probably safe way of checking if this file is tagged as a FAT file

    inputFile.seekg(0x0);
    int someNum;
    inputFile.read((char*)&someNum, sizeof(uint32_t));

    // this data represents "FAT ";
    return someNum == 542392646;
}
