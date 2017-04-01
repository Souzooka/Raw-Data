#include <iostream>
#include <fstream>
#include <vector>
#include "helpers.h"

using namespace std;

int main()
{
    std::string inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile(inputFilePath.c_str());
    getFileNameFromPath(inputFilePath);
    int iterations = getNumberOfFiles(inputFile);
    int * test = getFileDataPtrs(inputFile);

    for (int i = 0; i < iterations; ++i) {
        std::cout << std::hex << test[i] << endl;
    }
    return 0;
}
