#include <iostream>
#include <fstream>
#include "helpers.h"

using namespace std;

int main()
{
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    getNumberOfFiles(inputFile);
    return 0;
}
