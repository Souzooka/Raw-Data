#include <iostream>
#include <fstream>
#include <vector>
#include "helpers.h"

using namespace std;

int main()
{
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    getFileNameFromPath(inputFilePath);
    int * test = getFileLengths(inputFile);

    for (int i = 0; i < 13; ++i) {
        std::cout << std::hex << test[i] << endl;
    }
    return 0;
}
