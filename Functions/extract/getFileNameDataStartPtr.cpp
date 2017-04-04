#include <inttypes.h>
#include <fstream>

// returns the data pointer for the start of filenames
// THIS IS CURRENTLY UNUSED!
uint32_t getFileNameDataStartPtr(std::ifstream &inputFile)
{
    inputFile.seekg(0xF8);
    int nameDataPtr;
    inputFile.read((char*)&nameDataPtr, sizeof(uint32_t));

    return nameDataPtr;
}
