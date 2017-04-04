#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <boost/filesystem.hpp>

// returns an int representing how many files are in a directory and its subdirectories
int getFilesInDirectory (std::string filePath)
{
    int numFiles = 0;
    for(boost::filesystem::recursive_directory_iterator it(filePath); it != boost::filesystem::recursive_directory_iterator(); ++it)
    {
        numFiles++;
    }
    return numFiles;
}
