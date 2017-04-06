#include <inttypes.h>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

// returns filesizes of files in the directory
uint32_t* getFileSizesInDirectory(string filePath)
{
    uint32_t* fileSizes = new uint32_t[getFilesInDirectory(filePath)];
    string* fileNames = getFileNamesInDirectory(filePath);
    recursive_directory_iterator end_itr;

    for (int i = 0; i < getFilesInDirectory(filePath); ++i)
    {
        fileSizes[i] = file_size(fileNames[i]);
    }

    return fileSizes;
}
