#include <inttypes.h>
#include <iostream>
#include <fstream>

// This function will retrieve the number of files from a .FAT
uint32_t getNumberOfFiles(std::ifstream &inputFile)
{
    inputFile.seekg(0x4);
    int numOfFiles;
    inputFile.read((char*)&numOfFiles, sizeof(uint32_t));

    return numOfFiles;
}
