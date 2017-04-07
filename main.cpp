#define BOOST_SYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include "helpers.h"

using namespace std;

// This project's only dependency is Boost Filesystem (which requires Boost System).
// http://stackoverflow.com/questions/12578499/how-to-install-boost-on-ubuntu
// http://www.boost.org/

// NOTE: Most of the numbers in this project are uint_32 because due to the C++11 standard, minimum size of int is 2 bytes, which is too small for our tasks.
// Also, none of these pointers will be negative, of course, meaning uints are better for the needs of this project.

// TODO: Rebuild non-RD FATs (this is probably such a small change we can just shoehorn an if into the existing function)
// TODO: File validation (Boost catches some of this but some things can cause segmentation faults)

//tentative, will probably get refactored into fancy console arguments or a GUI and also be capable of fancy looping options

bool getFileOperationFromUser()
{
    cout << "Do you wish to [e]xtract or [r]ebuild a .DAT file?\n";
    char userResponse;

    while (true)
    {
        cin >> userResponse;
        if (userResponse == 'e' || userResponse == 'E')
        {
            return true;
        }
        else if (userResponse == 'r' || userResponse == 'R')
        {
            return false;
        }
        cout << "Do you wish to [e]xtract or [r]ebuild a .DAT file?\n";
    }
}

bool getFATTypeFromUser()
{
    cout << "Do you wish to rebuild a [R]aw Danger file, or a [G]eneric IREM file?\n";
    char userResponse;

    while (true)
    {
        cin >> userResponse;
        if (userResponse == 'r' || userResponse == 'R')
        {
            return true;
        }
        else if (userResponse == 'g' || userResponse == 'G')
        {
            return false;
        }
        cout << "Do you wish to rebuild a [R]aw Danger file, or a [G]eneric IREM file?\n";
    }
}

bool getInternalFromUser()
{
    cout << "Do you wish to build a file with an [e]xternal .FAT file (for big files), or with an [i]nternal header (for small files)?\n";
    char userResponse;

    while (true)
    {
        cin >> userResponse;
        if (userResponse == 'i' || userResponse == 'I')
        {
            return true;
        }
        else if (userResponse == 'e' || userResponse == 'E')
        {
            return false;
        }
        cout << "Do you wish to build a file with an [e]xternal .FAT file (for big files), or with an [i]nternal header (for small files)?\n";
    }
}

string getFolderPathFromUser()
{
    cout << "Enter the filepath of a folder to rebuild.\n";
    string inputFilePath;
    cin >> inputFilePath;
    return inputFilePath;
}

string getFilePathFromUser()
{
    cout << "Enter the filepath of a .DAT file to extract.\n";
    string inputFilePath;
    cin >> inputFilePath;
    return inputFilePath;
}

int gatherFileInfoAndCallExtract(std::string inputFilePath, bool internal)
{
    string fatFilePath;

    (internal) ? fatFilePath = inputFilePath : fatFilePath = inputFilePath.substr(0, inputFilePath.length() - 4) + ".FAT";

    string outputFolder = getPath(inputFilePath) + "/@" + getFileNameFromPath(inputFilePath);

    ifstream inputFile(inputFilePath.c_str());
    ifstream fatFile(fatFilePath.c_str());

    string* fileNames = getFileNames(fatFile);

    uint32_t numOfFiles = getNumberOfFiles(fatFile);
    uint32_t* fileLengths = getFileLengths(fatFile);
    uint32_t* fileLocations = getFileDataPtrs(fatFile);
    uint32_t fileOffset = getFileDataStartPtr(fatFile);

    extractFiles(inputFile, outputFolder, numOfFiles, fileNames, fileLengths, fileLocations, fileOffset, inputFilePath);
    return 0;
}

int main()
{
    char userResponse;
    while (true)
    {
        bool extract = getFileOperationFromUser();
        if (extract)
        {
            string inputFilePath = getFilePathFromUser();
            (isFatIncluded(inputFilePath)) ? gatherFileInfoAndCallExtract(inputFilePath, true) : gatherFileInfoAndCallExtract(inputFilePath, false);
        }
        else
        {
            cout << "Please enter in more information about the file you wish to rebuild.\n";
            // true = RD Fat, false = Generic Fat
            bool FATType = getFATTypeFromUser();
            // true = small FAT, false = big FAT
            bool internal = getInternalFromUser();
            string inputFolderPath = getFolderPathFromUser();

            if (internal)
            {
                FATType ? rebuildRDFat(inputFolderPath, true) : rebuildRDFat(inputFolderPath, true, false);
            }
            else
            {
                FATType ? rebuildRDFat(inputFolderPath, false) : rebuildRDFat(inputFolderPath, false, false);
            }
        }
        cout << "Do you wish to perform another operation? [y?]\n";
        cin >> userResponse;

        if (userResponse != 'y' && userResponse != 'Y')
        {
            break;
        }
    }

    return 0;
}

