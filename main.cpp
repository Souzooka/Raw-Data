#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
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

    //rebuildRDFat("test/@ROOT.DAT", false);
    std::string inputFilePath = getFilePathFromUser();
    std::ifstream inputFile(inputFilePath.c_str());
    std::string outputFolder = getPath(inputFilePath) + "/@" + getFileNameFromPath(inputFilePath);

    if (!isFatIncluded(inputFilePath))
    {
        std::string fatFilePath = inputFilePath.substr(0, inputFilePath.length() - 4) + ".FAT";
        std::ifstream fatFile(fatFilePath.c_str());
        int numOfFiles = getNumberOfFiles(fatFile);
        std::string * fileNames = getFileNames(fatFile);
        int * fileLengths = getFileLengths(fatFile);
        int * fileLocations = getFileDataPtrs(fatFile);
        int fileOffset = getFileDataStartPtr(fatFile);
        extractFiles(inputFile, outputFolder, numOfFiles, fileNames, fileLengths, fileLocations, fileOffset, inputFilePath);
    }
    else
    {
        int numOfFiles = getNumberOfFiles(inputFile);
        std::string * fileNames = getFileNames(inputFile);
        int * fileLengths = getFileLengths(inputFile);
        int * fileLocations = getFileDataPtrs(inputFile);
        int fileOffset = getFileDataStartPtr(inputFile);
        extractFiles(inputFile, outputFolder, numOfFiles, fileNames, fileLengths, fileLocations, fileOffset, inputFilePath);
    }


    return 0;
}

