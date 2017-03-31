#include <iostream>
#include <fstream>

bool isFatIncluded(std::ifstream &InputFile);

using namespace std;

int main()
{
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    return 0;
}
