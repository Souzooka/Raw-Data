#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../helpers.h"

// This function returns an array of data pointers for file names in a .FAT file.
// All strings being pointed at are null-terminated.
int* getFileNamePtrs(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int *arr;
    arr = new int[iterations];

    // For RD files
    if (isRDFile(inputFile))
    {
        inputFile.seekg(0xF8);
        inputFile.read((char*)&arr[0], sizeof(int));

        uint32_t currentPtr = 0x114;

        for (uint32_t i = 1; i < iterations; ++i)
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
