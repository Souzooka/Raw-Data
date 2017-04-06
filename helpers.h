#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

// helper functions
std::string getFileNameFromPath(std::string inputFilePath);
std::string getPath(std::string inputFilePath);
std::string cleanFileString(std::string filePath, std::string fileName);

// for extracting archives
bool isFatIncluded(std::string inputFilePath);
uint32_t getNumberOfFiles(std::ifstream &InputFile);
uint32_t getFileDataStartPtr(std::ifstream &inputFile);
uint32_t* getFileNamePtrs(std::ifstream &inputFile);
uint32_t* getFileLengths(std::ifstream &inputFile);
uint32_t* getFileDataPtrs(std::ifstream &inputFile);
std::string* getFileNames(std::ifstream &inputFile);
int extractFiles(std::ifstream &inputFile, std::string outputFolder, uint32_t numOfFiles, std::string * fileNames, uint32_t * fileLengths, uint32_t * fileLocations, uint32_t fileOffset, std::string inputFilePath);
bool isRDFile(std::ifstream &inputFile);

// for rebuilding archives
int rebuildEmptyFile(std::string fileName);
uint32_t getFilesInDirectory (std::string filePath);
std::string* getFileNamesInDirectory(std::string filePath);
uint32_t* getFileSizesInDirectory(std::string filePath);
int rebuildRDFat(std::string outputFolder, bool internal);
int appendDAT(std::string outputFolder, std::string* fileNames, uint32_t* fileSizes, uint32_t numOfFiles);
int createDAT(std::string outputFolder, std::string* fileNames, uint32_t* fileSizes, uint32_t numOfFiles);


#endif // HELPERS_H_INCLUDED
