#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <inttypes.h>

bool isFatIncluded(std::ifstream &InputFile);
uint32_t getNumberOfFiles(std::ifstream &InputFile);
std::string extractFileNameFromPath(std::string inputFilePath);

#endif // HELPERS_H_INCLUDED
