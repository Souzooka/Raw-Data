#include <inttypes.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../helpers.h"

// This function returns an array of the location of the start of files.
int* getFileDataPtrs(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int *arr;
    arr = new int[iterations];

    // For RD files
    inputFile.seekg(0xFC);
    inputFile.read((char*)&arr[0], sizeof(int));

    if (iterations > 1)
    {
        inputFile.seekg(0x104);
        inputFile.read((char*)&arr[1], sizeof(int));
    }

    uint32_t currentPtr = 0x118;

    for (uint32_t i = 2; i < iterations; ++i)
    {
        inputFile.seekg(currentPtr);
        inputFile.read((char*)&arr[i], sizeof(int));
        currentPtr += 0xC;
    }

    return arr;
}
