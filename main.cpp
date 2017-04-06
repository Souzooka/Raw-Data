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

int gatherFileInfoAndCallExtract(std::string inputFilePath, bool internal)
{
    std::string fatFilePath;

    if (!internal)
    {
        fatFilePath = inputFilePath.substr(0, inputFilePath.length() - 4) + ".FAT";
    }
    else
    {
        fatFilePath = inputFilePath;
    }

    std::string outputFolder = getPath(inputFilePath) + "/@" + getFileNameFromPath(inputFilePath);

    std::ifstream inputFile(inputFilePath.c_str());
    std::ifstream fatFile(fatFilePath.c_str());

    std::string * fileNames = getFileNames(fatFile);

    int numOfFiles = getNumberOfFiles(fatFile);
    int * fileLengths = getFileLengths(fatFile);
    int * fileLocations = getFileDataPtrs(fatFile);
    int fileOffset = getFileDataStartPtr(fatFile);

    extractFiles(inputFile, outputFolder, numOfFiles, fileNames, fileLengths, fileLocations, fileOffset, inputFilePath);
    return 0;
}

int main()
{

    // rebuildRDFat("test/@ROOT.DAT", false);
    std::string inputFilePath = getFilePathFromUser();

    if (!isFatIncluded(inputFilePath))
    {
        gatherFileInfoAndCallExtract(inputFilePath, false);
    }
    else
    {
        gatherFileInfoAndCallExtract(inputFilePath, true);
    }


    return 0;
}

