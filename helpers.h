#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <inttypes.h>

bool isFatIncluded(std::ifstream &InputFile);
uint32_t getNumberOfFiles(std::ifstream &InputFile);
std::string getFileNameFromPath(std::string inputFilePath);
uint32_t getFileNameDataStartPtr(std::ifstream &inputFile);
uint32_t getFileDataStartPtr(std::ifstream &inputFile);
int* getFileNamePtrs(std::ifstream &inputFile);
int* getFileLengths(std::ifstream &inputFile);
int* getFileDataPtrs(std::ifstream &inputFile);

#endif // HELPERS_H_INCLUDED
