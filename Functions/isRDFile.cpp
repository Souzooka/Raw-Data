#include <fstream>
#include <string.h>

using namespace std;

// this function checks if the .FAT file that is passed to the program is an RD or generic IREM FAT file,
// since generic files are padded, we probably just need to change how much the pointer increments in other functions
// The logic behind this function is that in RD files, data pointers in .FATs at 0xF8h and 0x108h are identical. (one points to start of filenames, other points to first filename)
// for generic files however, 0x108h is where padding starts so 0xF8h and 0x10Ch end up being identical instead.
// there is a possibility for error if the first padding value ends up actually pointing to the first filename,
// but since padding is usually something like "0x03000000" or "0xFFFFFFFF" this is a very low if impossible chance.
// Note: for reconstruction of these files the content of the padding seems to be completely irrelevant towards operation of the game
bool isRDFile(std::ifstream &inputFile)
{
    inputFile.seekg(0xF8);
    int base;
    inputFile.read((char*)&base, sizeof(int));

    inputFile.seekg(0x108);
    int compare;
    inputFile.read((char*)&compare, sizeof(int));

    return base == compare;
}
