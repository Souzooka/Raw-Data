#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <iostream>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

// returns an int representing how many files are in a directory and its subdirectories
int getFilesInDirectory (std::string filePath)
{
    int numFiles = 0;
    for(boost::filesystem::recursive_directory_iterator it(filePath); it != boost::filesystem::recursive_directory_iterator(); ++it)
    {
        if (is_regular_file(it->path()))
        {
            numFiles++;
        }
    }
    return numFiles;
}
