#include <inttypes.h>
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "../../helpers.h"

using namespace std;
using namespace boost::filesystem;

// returns an uint32_t representing how many files are in a directory and its subdirectories
uint32_t getFilesInDirectory (string filePath)
{
    uint32_t numFiles = 0;
    for(recursive_directory_iterator it(filePath); it != recursive_directory_iterator(); ++it)
    {
        if (is_regular_file(it->path()))
        {
            numFiles++;
        }
    }
    return numFiles;
}
