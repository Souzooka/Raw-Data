#include <inttypes.h>
#include <fstream>

uint32_t getFileNameDataStartPtr(std::ifstream &inputFile)
{
    inputFile.seekg(0xF8);
    int nameDataPtr;
    inputFile.read((char*)&nameDataPtr, sizeof(uint32_t));

    return nameDataPtr;
}
