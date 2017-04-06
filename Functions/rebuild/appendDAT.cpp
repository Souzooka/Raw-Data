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

// appends DAT to an existing FAT folder.
// The files in these DATs do NOT need to start at multiples at 0x800, (they *may* need to start at multiples of 0x10, not confirmed)
int appendDAT(std::string outputFolder, string* fileNames, int* fileSizes, int numOfFiles)
{
    ofstream outputFile;
    ifstream inputFile;
    path p(outputFolder);
    path returnPath(current_path());
    string file = p.filename().string().substr(1, p.filename().string().length() - 5) + ".FAT";
    string newFile = p.filename().string().substr(1, p.filename().string().length() - 5) + ".DAT";
    current_path(outputFolder);
    current_path("../");
    rename( file.c_str(), newFile.c_str() );
    outputFile.open(newFile.c_str(), std::ofstream::out | std::ofstream::app);
    outputFile.seekp(0, std::ios_base::end);
    current_path(returnPath);
    char smallemptybuffer[] = { 0x00 };

    for (int i = 0; i < numOfFiles; ++i)
    {
        std::cout << "Rebuilding file " << i << "\n";
        inputFile.open(fileNames[i].c_str());
        for (int j = 0; j < fileSizes[i]; ++j) {
            outputFile.put(inputFile.get());
        }
        while (outputFile.tellp() % 0x10 != 0x0) {
            outputFile.write(smallemptybuffer, 1);
        }
        inputFile.close();
    }
    current_path(returnPath);
    return 0;
}
