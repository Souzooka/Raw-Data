#include <inttypes.h>
#include <fstream>

// Note: if using this on an external .FAT, this will always return 0.
// This returns the "file data offset", e.g. if file data starts at 0x2F0 in a .DAT file, this will return 0x2F0.
uint32_t getFileDataStartPtr(std::ifstream &inputFile)
{
    inputFile.seekg(0xFC);
    uint32_t nameDataPtr;
    inputFile.read((char*)&nameDataPtr, sizeof(uint32_t));

    return nameDataPtr;
}
