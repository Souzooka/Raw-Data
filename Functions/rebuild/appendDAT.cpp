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

using namespace std;
using namespace boost::filesystem;

int appendDAT(std::string outputFolder)
{
    ofstream outputFile;
    ifstream inputFile;
    path p(outputFolder);
    path returnPath(current_path());
    string* fileNames = getFileNamesInDirectory(outputFolder);
    string file = p.filename().string().substr(1, p.filename().string().length() - 5) + ".FAT";
    string newFile = p.filename().string().substr(1, p.filename().string().length() - 5) + ".DAT";
    int numofFiles = getFilesInDirectory(outputFolder);
    int * fileSizes = getFileSizesInDirectory(outputFolder);
    current_path(outputFolder);
    current_path("../");
    rename( file.c_str(), newFile.c_str() );
    outputFile.open(newFile.c_str(), std::ofstream::out | std::ofstream::app);
    outputFile.seekp(0, std::ios_base::end);
    current_path(returnPath);
    char smallemptybuffer[] = { 0x00 };
    int roundedFileSizeBuffer;

    for (int i = 0; i < numofFiles; ++i)
    {
        std::cout << "Rebuilding file " << i << "\n";
        inputFile.open(fileNames[i].c_str());
        if (fileSizes[i] % 0x800 != 0x0)
        {
            roundedFileSizeBuffer = ((fileSizes[i] % 0x800) + 0x800) - (fileSizes[i] % 0x800 * 2);
        }
        for (int j = 0; j < fileSizes[i]; j++) {
            outputFile.put(inputFile.get());
        }
        for (int j = 0; j < roundedFileSizeBuffer; ++j) {
            outputFile.write(smallemptybuffer, 1);
        }
        inputFile.close();
    }
    current_path(returnPath);
    return 0;
}
