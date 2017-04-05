#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../../helpers.h"

// This function returns an array of data pointers for file names in a .FAT file.
// All strings being pointed at are null-terminated.
// probably needs a refactor so this function isn't junk
int* getFileNamePtrs(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int *arr;
    arr = new int[iterations];

    // For RD files
    if (isRDFile(inputFile))
    {
        uint32_t currentPtr = 0x108;

        for (uint32_t i = 0; i < iterations; ++i)
        {
            inputFile.seekg(currentPtr);
            inputFile.read((char*)&arr[i], sizeof(int));
            currentPtr += 0xC;
        }
    }
    else
    {
        uint32_t currentPtr = 0x10C;

        for (uint32_t i = 0; i < iterations; ++i)
        {
            inputFile.seekg(currentPtr);
            inputFile.read((char*)&arr[i], sizeof(int));
            currentPtr += 0x10;
        }
    }

    return arr;
}
