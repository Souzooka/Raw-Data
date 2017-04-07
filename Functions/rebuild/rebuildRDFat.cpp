#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <inttypes.h>
#include <iostream>
#include <fstream>
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

int rebuildRDFat(string outputFolder, bool internal, bool isRDFile)
{
    cout << "Gathering file information\n";

    path p(outputFolder);
    path returnPath(current_path());
    ofstream outputFile;
    uint32_t numofFiles = getFilesInDirectory(outputFolder);
    string* fileNames = getFileNamesInDirectory(outputFolder);
    uint32_t* fileSizes = getFileSizesInDirectory(outputFolder);
    int fileSizeBuffer;
    current_path(outputFolder);
    current_path("../");

    cout << "Rebuilding header\n";

    char fatbuffer[] = { 0x46, 0x41, 0x54, 0x20 };
    char paddingbuffer[] = { 0xFF, 0xFF, 0xFF, 0xFF };
    char emptybuffer[] = { 0x00, 0x00, 0x00, 0x00 };
    char smallemptybuffer[] = { 0x00 };
    char internalfatbuffer[] = { 0x02, 0x00, 0x00, 0x00 };
    char unknownbuffer[] = { 0x00, 0x01, 0x00, 0x00 };
    string file = p.filename().string().substr(1, p.filename().string().length() - 5) + ".FAT";
    outputFile.open(file.c_str());
    outputFile.write(fatbuffer, 4);
    outputFile.write(reinterpret_cast<const char *>(&numofFiles), sizeof(numofFiles));

    for (int i = 0; i < 3; ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    // if internal fat write this otherwise write emptybuffer
    (internal) ? outputFile.write(internalfatbuffer, 4) : outputFile.write(emptybuffer, 4);

    for (int i = 0; i < 55; ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    outputFile.write(unknownbuffer, 4);
    outputFile.write(emptybuffer, 4);
    outputFile.write(emptybuffer, 4);

    uint32_t fileInfoLength;
    isRDFile ? fileInfoLength = 3 : fileInfoLength = 4;

    for (uint32_t i = 0; i < (numofFiles * fileInfoLength); ++i)
    {
        outputFile.write(emptybuffer, 4);
    }

    uint32_t nameStart = outputFile.tellp();
    outputFile.seekp(0xF8);
    outputFile.write(reinterpret_cast<const char *>(&nameStart), sizeof(nameStart));
    outputFile.seekp(nameStart);

    uint32_t currentPtr;
    isRDFile ? currentPtr = 0x108 : currentPtr = 0x10C;

    uint32_t ptrIncrementer;
    isRDFile ? ptrIncrementer = 0xC : ptrIncrementer = 0x10;

    uint32_t endOfFile;

    for (uint32_t i = 0; i < numofFiles; ++i)
    {
        endOfFile = outputFile.tellp();
        outputFile.seekp(currentPtr);
        currentPtr += ptrIncrementer;
        outputFile.write(reinterpret_cast<const char *>(&endOfFile), sizeof(endOfFile));
        outputFile.seekp(endOfFile);
        outputFile << cleanFileString(outputFolder, fileNames[i]);
        outputFile.write(smallemptybuffer, 1);
    }

    // write null bytes until EOF is 0x10-synced
    while (outputFile.tellp() % 0x10 != 0x0)
    {
        outputFile.write(smallemptybuffer, 1);
    }

    // if internal write the EOF to 0xFC
    if (internal)
    {
        endOfFile = outputFile.tellp();
        outputFile.seekp(0xFC);
        outputFile.write(reinterpret_cast<const char *>(&endOfFile), sizeof(endOfFile));
    }

    currentPtr = 0x100;
    ptrIncrementer = 0x8;
    int fileSizeTotal = 0x0;

    for (uint32_t i = 0; i < numofFiles; ++i)
    {
        outputFile.seekp(currentPtr);
        outputFile.write(reinterpret_cast<const char *>(&fileSizeTotal), sizeof(fileSizeTotal));
        currentPtr += 0x4;
        outputFile.seekp(currentPtr);
        outputFile.write(reinterpret_cast<const char *>(&fileSizes[i]), sizeof(fileSizes[i]));

        if (!isRDFile)
        {
            currentPtr += 0x4;
            outputFile.seekp(currentPtr);
            outputFile.write(paddingbuffer, 4);
        }

        // organize files so that they are synced at certain points.
        // e.g. you wouldn't store a float at 0x2, you'd store it at 0x4 or 0x0, etc. This is the same concept.
        // this doesn't change how files are stored in the DAT portion -- just allows us to get the correct numbers for the header.
        if (!internal && fileSizes[i] % 0x800 != 0x0)
        {
            fileSizeBuffer = ((fileSizes[i] % 0x800) + 0x800) - (fileSizes[i] % 0x800 * 2);
        }
        else if (internal && fileSizes[i] % 0x10 != 0x0)
        {
            fileSizeBuffer = ((fileSizes[i] % 0x10) + 0x10) - (fileSizes[i] % 0x10 * 2);
        }
        else
        {
            // set/reset to 0 to avoid garbage
            fileSizeBuffer = 0;
        }

        fileSizeTotal += (fileSizeBuffer + fileSizes[i]);
        currentPtr += ptrIncrementer;
    }

    outputFile.close();
    current_path(returnPath);

    (internal) ? appendDAT(outputFolder, fileNames, fileSizes, numofFiles) : createDAT(outputFolder, fileNames, fileSizes, numofFiles);

    return 0;
}
