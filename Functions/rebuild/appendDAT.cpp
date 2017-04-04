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
    int numofFiles = getFilesInDirectory(outputFolder);
    current_path(outputFolder);
    current_path("../");
    outputFile.open(file.c_str(), std::ofstream::out | std::ofstream::app);
    outputFile.seekp(0, std::ios_base::end);
    cout << outputFile.tellp();

    for (int i = 0; i < numofFiles; ++i)
    {
        inputFile.open(fileNames[i].c_str());
        outputFile.put(inputFile.get());
        inputFile.close();
    }
    current_path(returnPath);
    return 0;
}
