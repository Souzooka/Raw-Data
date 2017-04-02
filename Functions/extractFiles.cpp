#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <algorithm>
#include "../helpers.h"

// This function will extract a .DAT file when given information from its header.
// NOTE: We should move all of these parameters *into* extractFiles,
// we need a helper function that'll locate a .FAT with the same name in this directory
int extractFiles(std::ifstream &inputFile, std::string outputFolder, int numOfFiles, std::string * fileNames, int * fileLengths, int * fileLocations, int fileOffset)
{
    boost::filesystem::create_directory(outputFolder);
    boost::filesystem::current_path(outputFolder);
    std::string fileName;
    std::ofstream files;

    for (int i = 0; i < numOfFiles; ++i)
    {
        std::replace( fileNames[i].begin(), fileNames[i].end(), '\\', '/' );
        std::stringstream a;
        a << getFileNameFromPath(fileNames[i]);
        std::cout << getFileNameFromPath(fileNames[i]) << std::endl;
        fileName = a.str();
        files.open(fileName.c_str());
        files.close();
    }
    return 0;
}
