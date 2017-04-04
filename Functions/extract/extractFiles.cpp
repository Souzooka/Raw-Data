#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include "../../helpers.h"

// This function will extract a .DAT file when given information from its header.
// NOTE: We should move all of these parameters *into* extractFiles,
// we need a helper function that'll locate a .FAT with the same name in this directory
int extractFiles(std::ifstream &inputFile, std::string outputFolder, int numOfFiles, std::string * fileNames, int * fileLengths, int * fileLocations, int fileOffset)
{
    boost::filesystem::create_directory(outputFolder);
    boost::filesystem::path canonicalOutputFolder = boost::filesystem::canonical(outputFolder);
    boost::filesystem::current_path(canonicalOutputFolder);
    int dataOffset = fileOffset;
    std::string fileName;
    std::string filePath;
    std::ofstream outputFile;

    if (!isFatIncluded(inputFile))
    {
        dataOffset = 0;
    }

    inputFile.seekg(dataOffset);
    for (int i = 0; i < numOfFiles; ++i)
    {
        inputFile.seekg(fileLocations[i] + dataOffset);

        std::replace( fileNames[i].begin(), fileNames[i].end(), '\\', '/' );
        fileName = getFileNameFromPath(fileNames[i]);
        filePath = getPath(fileNames[i]);

        boost::filesystem::create_directories(filePath);
        boost::filesystem::current_path(filePath);

        outputFile.open(fileName.c_str());

        for (int j = 0; j < fileLengths[i]; j++) {
            outputFile.put(inputFile.get());
        }
        outputFile.close();

        boost::filesystem::current_path(canonicalOutputFolder);
    }
    return 0;
}
