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

string* getFileNamesInDirectory(string filePath)
{
    path p (filePath);
    string* fileNames = new std::string[getFilesInDirectory(filePath)];
    recursive_directory_iterator end_itr;
    int incrementer = 0;

    // cycle through the directory
    for (recursive_directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            fileNames[incrementer] = itr->path().string();
            cout << fileNames[incrementer] << endl;
        }
        ++incrementer;
    }

    return fileNames;
}
