#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

bool isFatIncluded(std::ifstream &InputFile)
{
    char buffer[4];
    InputFile >> buffer;

    if (!strcmp(buffer, "FAT"))
    {
        return true;
    }
    else
    {
        return false;
    }
}
