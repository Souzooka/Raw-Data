#include <inttypes.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../../helpers.h"

// This function returns an array of the location of the start of files.
// probably needs a refactor so this function isn't junk
int* getFileDataPtrs(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int *arr;
    arr = new int[iterations];

    // For RD files
    if (isRDFile(inputFile))
    {
        uint32_t currentPtr = 0x100;

        for (uint32_t i = 0; i < iterations; ++i)
        {
            inputFile.seekg(currentPtr);
            inputFile.read((char*)&arr[i], sizeof(int));
            currentPtr += 0xC;
        }
    }
    // for generic files
    else
    {
        uint32_t currentPtr = 0x100;

        for (uint32_t i = 0; i < iterations; ++i)
        {
            inputFile.seekg(currentPtr);
            inputFile.read((char*)&arr[i], sizeof(int));
            currentPtr += 0x10;
        }
    }

    return arr;
}
