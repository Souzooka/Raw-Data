#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <inttypes.h>
#include <iostream>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

int* getFileSizesInDirectory(string filePath)
{
    int* fileSizes = new int[getFilesInDirectory(filePath)];
    string* fileNames = getFileNamesInDirectory(filePath);
    recursive_directory_iterator end_itr;

    // cycle through the directory
    for (int i = 0; i < getFilesInDirectory(filePath); ++i)
    {
        fileSizes[i] = file_size(fileNames[i]);
    }

    return fileSizes;
}
