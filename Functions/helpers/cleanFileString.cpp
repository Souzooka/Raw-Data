#include <string>
#include <algorithm>

using namespace std;

// This function replaces a directory path string with a string acceptable for .FAT Headers.
string cleanFileString(string fileName, string filePath)
{
    filePath = filePath.substr(fileName.length() + 1);
    replace( filePath.begin(), filePath.end(), '/', '\\' );
    return filePath;
}
