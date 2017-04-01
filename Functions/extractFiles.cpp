#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include "../helpers.h"

// This function will extract a .DAT file when given information from its header.
// NOTE: We should move all of these parameters *into* extractFiles,
// we need a helper function that'll locate a .FAT with the same name in this directory
int extractFiles(std::ifstream &inputFile, std::string outputFolder, int numOfFiles, std::string * fileNames, int * fileLengths, int * fileLocations, int fileOffset)
{
    std::cout << outputFolder;
    boost::filesystem::create_directory(outputFolder);
    return 0;
}
