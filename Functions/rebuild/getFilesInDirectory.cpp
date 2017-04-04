#include <stdio.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <boost/filesystem.hpp>

int getFilesInDirectory (std::string filePath)
{
    int numFiles = 0;
    for(boost::filesystem::recursive_directory_iterator it(filePath); it != boost::filesystem::recursive_directory_iterator(); ++it)
    {
        numFiles++;
    }
    return numFiles;
}
