#include <iostream>
#include <fstream>
#include <vector>
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include "helpers.h"

using namespace std;

//tentative, will probably get refactored into fancy console arguments or a GUI and also be capable of fancy recursion options
std::string getFilePathFromUser()
{
    cout << "Enter the filepath of a .DAT file to extract" << endl;
    std::string inputFilePath;
    cin >> inputFilePath;
    return inputFilePath;
}

int main()
{
    std::string inputFilePath = getFilePathFromUser();
    std::ifstream inputFile(inputFilePath.c_str());

    std::string outputFolder = getPath(inputFilePath) + "/@" + getFileNameFromPath(inputFilePath);
    int numOfFiles = getNumberOfFiles(inputFile);
    std::string * fileNames = getFileNames(inputFile);
    int * fileLengths = getFileLengths(inputFile);
    int * fileLocations = getFileDataPtrs(inputFile);
    int fileOffset = getFileDataStartPtr(inputFile);
    extractFiles(inputFile, outputFolder, numOfFiles, fileNames, fileLengths, fileLocations, fileOffset);

    return 0;
}
