// tests.cpp
#include "Functions/isFatIncluded.cpp"
#include "Functions/getNumberOfFiles.cpp"
#include "Functions/getFileNameFromPath.cpp"
#include "Functions/getFileNameDataStartPtr.cpp"
#include "Functions/getFileDataStartPtr.cpp"
#include "Functions/getFileNamePtrs.cpp"
#include "Functions/getFileLengths.cpp"
#include "Functions/getFileDataPtrs.cpp"
#include "Functions/getFileNames.cpp"
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
    int * test = getFileNamePtrs(inputFile);

    ASSERT_EQ(0x130, test[0]);
    ASSERT_EQ(0x158, test[1]);
    ASSERT_EQ(0x17A, test[2]);
    ASSERT_EQ(0x19F, test[3]);

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    test = getFileNamePtrs(inputFile2);

    ASSERT_EQ(0x19C, test[0]);
    ASSERT_EQ(0x1AC, test[1]);
    ASSERT_EQ(0x1BB, test[2]);
    ASSERT_EQ(0x1C9, test[3]);
    ASSERT_EQ(0x1D6, test[4]);
    ASSERT_EQ(0x1E9, test[5]);
    ASSERT_EQ(0x1F7, test[6]);
    ASSERT_EQ(0x206, test[7]);
    ASSERT_EQ(0x216, test[8]);
    ASSERT_EQ(0x226, test[9]);
    ASSERT_EQ(0x237, test[10]);
    ASSERT_EQ(0x247, test[11]);
    ASSERT_EQ(0x258, test[12]);
}

TEST(getFileLengths, ReturnArrOfLengths) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    int * test = getFileLengths(inputFile);

    ASSERT_EQ(0x5200, test[0]);
    ASSERT_EQ(0x37B0, test[1]);
    ASSERT_EQ(0x58F0, test[2]);
    ASSERT_EQ(0x3C80, test[3]);

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    test = getFileLengths(inputFile2);

    ASSERT_EQ(0x1A00, test[0]);
    ASSERT_EQ(0x3D25, test[1]);
    ASSERT_EQ(0x2C19, test[2]);
    ASSERT_EQ(0x2505, test[3]);
    ASSERT_EQ(0x4Ef5, test[4]);
    ASSERT_EQ(0x7585, test[5]);
    ASSERT_EQ(0x23C9, test[6]);
    ASSERT_EQ(0xF63D, test[7]);
    ASSERT_EQ(0x55B5, test[8]);
    ASSERT_EQ(0x4A7d, test[9]);
    ASSERT_EQ(0x24B1, test[10]);
    ASSERT_EQ(0x79B0, test[11]);
    ASSERT_EQ(0x82F1,  test[12]);
}

TEST(getFileDataPtrs, ReturnArrOfDataPtrs) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    int * test = getFileDataPtrs(inputFile);

    ASSERT_EQ(0x1D0, test[0]);
    ASSERT_EQ(0x5200, test[1]);
    ASSERT_EQ(0x89B0, test[2]);
    ASSERT_EQ(0xE2A0, test[3]);

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    test = getFileDataPtrs(inputFile2);

    ASSERT_EQ(0x270, test[0]);
    ASSERT_EQ(0x19F1, test[1]);
    ASSERT_EQ(0x5730, test[2]);
    ASSERT_EQ(0x8350, test[3]);
    ASSERT_EQ(0xA860, test[4]);
    ASSERT_EQ(0xF760, test[5]);
    ASSERT_EQ(0x16CF0, test[6]);
    ASSERT_EQ(0x190C0, test[7]);
    ASSERT_EQ(0x28700, test[8]);
    ASSERT_EQ(0x2DCC0, test[9]);
    ASSERT_EQ(0x32740, test[10]);
    ASSERT_EQ(0x34C00, test[11]);
    ASSERT_EQ(0x3C5B0,  test[12]);
}

TEST(getFileNames, ReturnArrOfNames) {
    std::string inputFilePath = "test/TEST.DAT";
    std::ifstream inputFile(inputFilePath.c_str());
    std::string * test = getFileNames(inputFile);

    ASSERT_EQ("IMD\\CHR\\PL01\\P01_KYATATU_WALK_START.IMD", test[0]);
    ASSERT_EQ("IMD\\CHR\\PL01\\P01_KYATATU_WAIT.IMD", test[1]);
    ASSERT_EQ("IMD\\CHR\\PL01\\P01_KYATATU_WALK_LP.IMD", test[2]);
    ASSERT_EQ("IMD\\CHR\\PL01\\P01_KYATATU_WALK_END.IMD", test[3]);

    inputFilePath = "test/IOP.FAT";
    std::ifstream inputFile2(inputFilePath.c_str());
    test = getFileNames(inputFile2);

    ASSERT_EQ("IOP\\SIO2MAN.IRX", test[0]);
    ASSERT_EQ("IOP\\DBCMAN.IRX", test[1]);
    ASSERT_EQ("IOP\\SIO2D.IRX", test[2]);
    ASSERT_EQ("IOP\\DS1U.IRX", test[3]);
    ASSERT_EQ("IOP\\MC2\\MC2_S1.IRX", test[4]);
    ASSERT_EQ("IOP\\LIBSD.IRX", test[5]);
    ASSERT_EQ("IOP\\SDRDRV.IRX", test[6]);
    ASSERT_EQ("IOP\\MODHSYN.IRX", test[7]);
    ASSERT_EQ("IOP\\MODMIDI.IRX", test[8]);
    ASSERT_EQ("IOP\\MODSESQ2.IRX", test[9]);
    ASSERT_EQ("IOP\\MODSEIN.IRX", test[10]);
    ASSERT_EQ("IOP\\IREMSND2.IRX", test[11]);
    ASSERT_EQ("IOP\\CDVDSTM.IRX",  test[12]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
