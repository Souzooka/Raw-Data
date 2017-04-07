#include <inttypes.h>
#include <fstream>
#include "../../helpers.h"

using namespace std;

// This function returns an array of the location of the start of files.
// probably needs a refactor so this function isn't junk
uint32_t* getFileDataPtrs(ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    uint32_t *arr = new uint32_t[iterations];
    uint32_t ptrIncrementer;
    uint32_t currentPtr = 0x100;

    (isRDFile(inputFile)) ? ptrIncrementer = 0xC : ptrIncrementer = 0x10;

    for (uint32_t i = 0; i < iterations; ++i)
    {
        inputFile.seekg(currentPtr);
        inputFile.read((char*)&arr[i], sizeof(uint32_t));
        currentPtr += ptrIncrementer;
    }

    return arr;
}
