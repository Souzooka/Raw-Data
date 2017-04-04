#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

// helper functions
std::string getFileNameFromPath(std::string inputFilePath);
std::string getPath(std::string inputFilePath);
std::string cleanFileString(std::string filePath, std::string fileName);

// for extracting archives
bool isFatIncluded(std::ifstream &InputFile);
uint32_t getNumberOfFiles(std::ifstream &InputFile);
uint32_t getFileNameDataStartPtr(std::ifstream &inputFile);
uint32_t getFileDataStartPtr(std::ifstream &inputFile);
int* getFileNamePtrs(std::ifstream &inputFile);
int* getFileLengths(std::ifstream &inputFile);
int* getFileDataPtrs(std::ifstream &inputFile);
std::string* getFileNames(std::ifstream &inputFile);
int extractFiles(std::ifstream &inputFile, std::string outputFolder, int numOfFiles, std::string * fileNames, int * fileLengths, int * fileLocations, int fileOffset);
bool isRDFile(std::ifstream &inputFile);

// for rebuilding archives
int rebuildEmptyFile(std::string fileName);
int getFilesInDirectory (std::string filePath);
std::string* getFileNamesInDirectory(std::string filePath);
int* getFileSizesInDirectory(std::string filePath);
int rebuildRDFat(std::string outputFolder);


#endif // HELPERS_H_INCLUDED
