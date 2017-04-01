#include <iostream>
#include <fstream>
#include <vector>
#include "helpers.h"

using namespace std;

int main()
{
    std::string inputFilePath = "test/ROOT.FAT";
    std::ifstream inputFile(inputFilePath.c_str());
    getFileNameFromPath(inputFilePath);
    int iterations = getNumberOfFiles(inputFile);
    std::string * test = getFileNames(inputFile);

    for (int i = 0; i < iterations; ++i) {
        std::cout << test[i] << endl;
    }
    return 0;
}
