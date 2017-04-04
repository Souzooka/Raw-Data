#include <string>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <algorithm>

std::string cleanFileString(std::string fileName, std::string filePath)
{
    filePath = filePath.substr(fileName.length() + 1);
    std::replace( filePath.begin(), filePath.end(), '/', '\\' );
    return filePath;
}
