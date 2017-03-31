// tests.cpp
#include "isFatIncluded.cpp"
#include <gtest/gtest.h>
#include <fstream>

TEST(isFatIncluded, General) {
    std::string inputFilePath = "test/TEST.DAT";
    std::string decoyFilePath = "test/DECOY.DAT";

    std::ifstream inputFile(inputFilePath.c_str());
    std::ifstream decoyFile(decoyFilePath.c_str());

    ASSERT_EQ(true, isFatIncluded(inputFile));
    ASSERT_EQ(false, isFatIncluded(decoyFile));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
