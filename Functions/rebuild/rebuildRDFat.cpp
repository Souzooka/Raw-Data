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

int rebuildRDFat(std::string outputFolder)
{
    path p(outputFolder);
    ofstream outputFile;
    int numofFiles = getFilesInDirectory(outputFolder);
    string* fileNames = getFileNamesInDirectory(outputFolder);
    int* fileSizes = getFileSizesInDirectory(outputFolder);
    current_path(outputFolder);
    current_path("../");

    char fatbuffer[] = { 0x46, 0x41, 0x54, 0x20 };
    char emptybuffer[] = { 0x00, 0x00, 0x00, 0x00 };
    char smallemptybuffer[] = { 0x00 };
    char externalfatbuffer[] = { 0x02, 0x00, 0x00, 0x00 };
    char unknownbuffer[] = { 0x00, 0x01, 0x00, 0x00 };
    string file = p.filename().string().substr(1, p.filename().string().length() - 5) + ".FAT";
    outputFile.open(file.c_str());
    outputFile.write(fatbuffer, 4);
    outputFile.write(reinterpret_cast<const char *>(&numofFiles), sizeof(numofFiles));

    for (int i = 0; i < 3; ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    outputFile.write(externalfatbuffer, 4);

    for (int i = 0; i < 55; ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    outputFile.write(unknownbuffer, 4);
    // 0xF8 -- filename pointer
    outputFile.write(emptybuffer, 4);
    // 0xFC -- filedata pointer
    outputFile.write(emptybuffer, 4);

    // all the data pointer stuff goes here

    // three (3 used here) pointer types:
    // filestarts
    // filelengths
    // filenames
    for (int i = 0; i < (numofFiles * 3); ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    int nameStart = outputFile.tellp();
    outputFile.seekp(0xF8);
    outputFile.write(reinterpret_cast<const char *>(&nameStart), sizeof(nameStart));

    outputFile.seekp(nameStart);

    int currentPtr = 0x108;
    int endOfFile = 0;

    for (int i = 0; i < numofFiles; ++i)
    {
        endOfFile = outputFile.tellp();
        outputFile.seekp(currentPtr);
        currentPtr += 0xC;
        outputFile.write(reinterpret_cast<const char *>(&endOfFile), sizeof(endOfFile));
        outputFile.seekp(endOfFile);
        outputFile << cleanFileString(outputFolder, fileNames[i]);
        outputFile.write(smallemptybuffer, 1);
    }

    // pls refactor this whole file basically
    int stop = (outputFile.tellp() % 16 * -1 + 16);
    for (int i = 0; i < stop; ++i)
    {
        outputFile.write(smallemptybuffer, 1);
    }

    endOfFile = outputFile.tellp();
    outputFile.seekp(0xFC);
    outputFile.write(reinterpret_cast<const char *>(&endOfFile), sizeof(endOfFile));

    currentPtr = 0x100;
    int fileSizeTotal = 0x0;

    for (int i = 0; i < numofFiles; ++i)
    {
        outputFile.seekp(currentPtr);
        outputFile.write(reinterpret_cast<const char *>(&fileSizeTotal), sizeof(fileSizeTotal));
        currentPtr += 0x4;
        outputFile.seekp(currentPtr);
        outputFile.write(reinterpret_cast<const char *>(&fileSizes[i]), sizeof(fileSizes[i]));
        fileSizeTotal += fileSizes[i];
        currentPtr += 0x8;
    }

    return 0;
}
