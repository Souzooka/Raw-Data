#include <inttypes.h>
#include <fstream>
#include "../../helpers.h"

using namespace std;

// This function returns an array of data pointers for file names in a .FAT file.
// All strings being pointed at are null-terminated.
// probably needs a refactor so this function isn't junk
uint32_t* getFileNamePtrs(ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    uint32_t *arr = new uint32_t[iterations];
    uint32_t ptrIncrementer;
    uint32_t currentPtr;

    // since the header in older FATs are padded, we need to change our initial starting location
    // due to padding being inserted before the filename pointers
    (isRDFile(inputFile)) ? ptrIncrementer = 0xC : 0x10;
    (isRDFile(inputFile)) ? currentPtr = 0x108 : 0x10C;

    for (uint32_t i = 0; i < iterations; ++i)
    {
        inputFile.seekg(currentPtr);
        inputFile.read((char*)&arr[i], sizeof(uint32_t));
        currentPtr += ptrIncrementer;
    }

    return arr;
}
