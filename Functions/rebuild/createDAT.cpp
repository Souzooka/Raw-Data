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

int createDAT(std::string outputFolder)
{
    ofstream outputFile;
    ifstream inputFile;
    path p(outputFolder);
    path returnPath(current_path());
    string* fileNames = getFileNamesInDirectory(outputFolder);
    string file = p.filename().string().substr(1, p.filename().string().length() - 5) + ".DAT";
    int numofFiles = getFilesInDirectory(outputFolder);
    int * fileSizes = getFileSizesInDirectory(outputFolder);
    current_path(outputFolder);
    current_path("../");
    outputFile.open(file.c_str());
    current_path(returnPath);
    int roundedFileSizeBuffer;
    char smallemptybuffer[] = { 0x00 };

    for (int i = 0; i < numofFiles; ++i)
    {
        std::cout << "Rebuilding file " << i << "\n";
        inputFile.open(fileNames[i].c_str());
        for (int j = 0; j < fileSizes[i]; j++) {
            outputFile.put(inputFile.get());
        }
        while (outputFile.tellp() % 0x800 != 0x0) {
            outputFile.write(smallemptybuffer, 1);
        }
        inputFile.close();
    }
    current_path(returnPath);
    return 0;
}
