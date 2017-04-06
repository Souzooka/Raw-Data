#include <inttypes.h>
#include <fstream>

// This function will retrieve the number of files from a .FAT
uint32_t getNumberOfFiles(std::ifstream &inputFile)
{
    inputFile.seekg(0x4);
    uint32_t numOfFiles;
    inputFile.read((char*)&numOfFiles, sizeof(uint32_t));

    return numOfFiles;
}
