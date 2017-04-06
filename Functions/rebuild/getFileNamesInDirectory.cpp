#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

string* getFileNamesInDirectory(string filePath)
{
    path p (filePath);
    string* fileNames = new string[getFilesInDirectory(filePath)];
    recursive_directory_iterator end_itr;
    int incrementer = 0;

    // cycle through the directory
    for (recursive_directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // if it's a file
        if (is_regular_file(itr->path())) {
            // assign the current filename to our array of strings
            fileNames[incrementer] = itr->path().string();
            ++incrementer;
        }
    }

    return fileNames;
}
