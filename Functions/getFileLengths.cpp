#include <inttypes.h>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../helpers.h"

// This function returns a list of data pointers for file names in a .FAT file as an int array.
// All strings being pointed at are null-terminated.
int* getFileLengths(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int *arr;
    arr = new int[iterations];

    // For RD files
    inputFile.seekg(0x10C);
    inputFile.read((char*)&arr[0], sizeof(int));

    uint32_t currentPtr = 0x110;

    for (uint32_t i = 1; i < iterations; ++i)
    {
        inputFile.seekg(currentPtr);
        inputFile.read((char*)&arr[i], sizeof(int));
        currentPtr += 0xC;
    }

    return arr;
}
