#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <inttypes.h>
#include <fstream>
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

// This function will extract a .DAT file when given information from its header.
// NOTE: We should move all of these parameters *into* extractFiles,
// we need a helper function that'll locate a .FAT with the same name in this directory
int extractFiles(ifstream &inputFile, string outputFolder, uint32_t numOfFiles, string * fileNames, uint32_t * fileLengths, uint32_t * fileLocations, uint32_t fileOffset, string inputFilePath)
{
    string fileName;
    string filePath;
    ofstream outputFile;

    // create a folder to house our extracted files and move into it
    create_directory(outputFolder);
    path canonicalOutputFolder = canonical(outputFolder);
    current_path(canonicalOutputFolder);

    // set the filedata offset to 0x0 if the FAT isn't in this DAT
    if (!isFatIncluded(inputFilePath))
    {
        fileOffset = 0;
    }

    inputFile.seekg(fileOffset);

    // for each file, create and move into each new directory and create a new file with the data.
    for (uint32_t i = 0; i < numOfFiles; ++i)
    {
        inputFile.seekg(fileLocations[i] + fileOffset);

        replace( fileNames[i].begin(), fileNames[i].end(), '\\', '/' );
        fileName = getFileNameFromPath(fileNames[i]);
        filePath = getPath(fileNames[i]);

        create_directories(filePath);
        current_path(filePath);

        outputFile.open(fileName.c_str());

        for (uint32_t j = 0; j < fileLengths[i]; j++) {
            outputFile.put(inputFile.get());
        }
        outputFile.close();

        current_path(canonicalOutputFolder);
    }
    return 0;
}
