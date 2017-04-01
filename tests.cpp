// tests.cpp
#include "Functions/isFatIncluded.cpp"
#include "Functions/getNumberOfFiles.cpp"
#include "Functions/extractFileNameFromPath.cpp"
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
}

TEST(extractFileNameFromPath, ReturnFileName) {
    std::string inputFilePath = "test/TEST.DAT";
    ASSERT_EQ("TEST.DAT", extractFileNameFromPath(inputFilePath));
    inputFilePath = "@ROOT/AREA_01/SOMEFILENAME.DAT";
    ASSERT_EQ("SOMEFILENAME.DAT", extractFileNameFromPath(inputFilePath));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
