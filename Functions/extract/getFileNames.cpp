#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "../../helpers.h"

// This function returns an array of strings of file names in a .FAT file.
// All strings are null-terminated.
std::string* getFileNames(std::ifstream &inputFile)
{
    uint32_t iterations = getNumberOfFiles(inputFile);
    int * namePtrs = getFileNamePtrs(inputFile);
    std::string* fileNames = new std::string[iterations];

    uint32_t currentPtr;

    for (uint32_t i = 0; i < iterations; ++i)
    {
        currentPtr = namePtrs[i];
        inputFile.seekg(currentPtr);
        std::getline(inputFile, fileNames[i], '\0');
    }

    return fileNames;
}
