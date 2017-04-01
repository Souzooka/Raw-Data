// tests.cpp
#include "Functions/isFatIncluded.cpp"
#include "Functions/getNumberOfFiles.cpp"
#include "Functions/getFileNameFromPath.cpp"
#include "Functions/getFileNameDataStartPtr.cpp"
#include "Functions/getFileDataStartPtr.cpp"
#include "Functions/getListOfFileNamePtrs.cpp"
#include <gtest/gtest.h>
#include <fstream>
#include <inttypes.h>

TEST(isFatIncluded, ShouldVerifyFat) {
    std::string inputFilePath = "test/TEST.DAT";
    std::string decoyFilePath = "test/DECOY.DAT";

    std::ifstream inputFile(inputFilePath.c_str());
    std::ifstream decoyFile(decoyFilePath.c_str());

    ASSERT_EQ(true, isFatIncluded(inputFile));
    ASSERT_EQ(false, isFatIncluded(decoyFile));
}

TEST(getNumberOfFiles, ShouldCountFiles) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    ASSERT_EQ(4, getNumberOfFiles(inputFile));

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    ASSERT_EQ(13, getNumberOfFiles(inputFile2));
}

TEST(getFileNameFromPath, ReturnFileName) {
    std::string inputFilePath = "test/TEST.DAT";
    ASSERT_EQ("TEST.DAT", getFileNameFromPath(inputFilePath));
    inputFilePath = "@ROOT/AREA_01/SOMEFILENAME.DAT";
    ASSERT_EQ("SOMEFILENAME.DAT", getFileNameFromPath(inputFilePath));
}

TEST(getFileNameDataStartPtr, ReturnFileNameDataPtr) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    ASSERT_EQ(0x130, getFileNameDataStartPtr(inputFile));

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    ASSERT_EQ(0x19C, getFileNameDataStartPtr(inputFile2));
}

TEST(getFileDataStartPtr, ReturnFileDataPtr) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    ASSERT_EQ(0x1D0, getFileDataStartPtr(inputFile));

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    ASSERT_EQ(0x270, getFileDataStartPtr(inputFile2));
}

TEST(getListOfFileNamePtrs, ReturnFileNamePtrs) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    int * test = getListOfFileNamePtrs(inputFile);

    ASSERT_EQ(0x130, test[0]);
    ASSERT_EQ(0x158, test[1]);
    ASSERT_EQ(0x17a, test[2]);
    ASSERT_EQ(0x19f, test[3]);

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    test = getListOfFileNamePtrs(inputFile2);

    ASSERT_EQ(0x19C, test[0]);
    ASSERT_EQ(0x1aC, test[1]);
    ASSERT_EQ(0x1bb, test[2]);
    ASSERT_EQ(0x1c9, test[3]);
    ASSERT_EQ(0x1d6, test[4]);
    ASSERT_EQ(0x1e9, test[5]);
    ASSERT_EQ(0x1f7, test[6]);
    ASSERT_EQ(0x206, test[7]);
    ASSERT_EQ(0x216, test[8]);
    ASSERT_EQ(0x226, test[9]);
    ASSERT_EQ(0x237, test[10]);
    ASSERT_EQ(0x247, test[11]);
    ASSERT_EQ(0x258, test[12]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
