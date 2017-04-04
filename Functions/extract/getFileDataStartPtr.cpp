#include <inttypes.h>
#include <fstream>

// Note: if using this on an external .FAT, this will always return 0.
uint32_t getFileDataStartPtr(std::ifstream &inputFile)
{
    inputFile.seekg(0xFC);
    int nameDataPtr;
    inputFile.read((char*)&nameDataPtr, sizeof(uint32_t));

    return nameDataPtr;
}
