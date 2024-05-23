﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../TestShell/TestShellApplication.cpp"
#include <fstream>
#include "MOCKCommand.cpp"
#include "../TestShell/ReadCommand.cpp"
#include "../TestShell/WriteCommand.cpp"
#include <stdexcept>

using namespace std;
using namespace testing;

// Test case for ReadCommand
TEST(CommandTest, ReadCommand) {
    MockReceiver mockReceiver;
    EXPECT_CALL(mockReceiver, read()).Times(AtLeast(1));

    ReadCommand readCommand(&mockReceiver);
    readCommand.execute({});
}

// Test case for WriteCommand
TEST(CommandTest, WriteCommand) {
    MockReceiver mockReceiver;
    EXPECT_CALL(mockReceiver, write()).Times(AtLeast(1));

    WriteCommand writeCommand(&mockReceiver);
    writeCommand.execute({});
}

TEST(TestShellApplicationTest, WriteCommandTest) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestShellApplicationTest, ReadCommandTest) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestShellApplicationTest, HelpCommandTest) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestShellApplicationTest, ExitCommandTest) {
    TestShellApplication app;
    std::string str = "exit";

    EXPECT_TRUE(app.execute(str));
}

TEST(TestShellApplicationTest, FullReadCommandTest) {
    //TODO
    //cout 결과를 strCout에 저장되게함
    //std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    //std::ostringstream strCout;
    //std::cout.rdbuf(strCout.rdbuf());

    //TestShellApplication testShell;
    //FullReadCommand fullreadCmd;
    //WriteCommand writeCmd;
    //
    //for (int lba = 0; lba < 100; lba++) 
    //{
    //    vector<string> v = { "write", to_string(lba), "0X12345678", " "};
    //    testShell.executeCommand(&writeCmd, v);
    //}

    //vector<string> v = { "fullread", " " };
    //testShell.executeCommand(&fullreadCmd, v);
 

    //
    //std::string expected = "";
    //for (int lba = 0; lba < 100; lba++)
    //{
    //    expected += "0X12345678\n";
    //}
    //std::cout.rdbuf(oldCoutStreamBuf);
    //EXPECT_THAT(strCout.str(), testing::Eq(expected));
    
}


TEST(TestShellApplicationTest, FullWriteCommandTest) {
    //TODO
    //cout 결과를 strCout에 저장되게함
    //std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    //std::ostringstream strCout;
    //std::cout.rdbuf(strCout.rdbuf());

    //TestShellApplication testShell;
    //FullWriteCommand fullwriteCmd;
    //FullReadCommand fullreadCmd;

    //vector<string> v = { "fullwrite", "0X12345678", " " };
    //testShell.executeCommand(&fullwriteCmd, v);
    //v = { "fullread", " " };
    //testShell.executeCommand(&fullreadCmd, v);

    //std::string expected = "";
    //for (int lba = 0; lba < 100; lba++)
    //{
    //    expected += "0X12345678\n";
    //}
    //std::cout.rdbuf(oldCoutStreamBuf);
    //EXPECT_THAT(strCout.str(), testing::Eq(expected));

}

TEST(TestShellApplicationTest, TestApp1CommandTest) {
    TestShellApplication app;
    std::string str = "testapp1";

    EXPECT_TRUE(app.execute(str));
}

TEST(TestShellApplicationTest, TestApp2CommandTest) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(ReadCommand, TestExecuteInvalidArgument) {
    MockReceiver mockReceiver;
    ReadCommand readCommand(&mockReceiver);
    EXPECT_THROW(readCommand.execute({}), invalid_argument);
}

TEST(ReadCommand, TestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "r", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST(WriteCommand, TestExecuteInvalidArgument) {
    MockReceiver mockReceiver;
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({}), invalid_argument);
}
