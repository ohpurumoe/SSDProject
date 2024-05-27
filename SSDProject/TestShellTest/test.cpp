﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../TestShell/TestShellApplication.cpp"
#include <fstream>
#include "MOCKCommand.cpp"

#include <stdexcept>

using namespace std;
using namespace testing;

class TestShellApplicationFixture : public Test {
public:
    void SetUp() override {
        oldCoutStreamBuf = std::cout.rdbuf();
        cout.rdbuf(strCout.rdbuf());

        fullreadCmd = new FullReadCommand(&receiver);
        writeCmd = new WriteCommand(&receiver);
        fullwriteCmd = new FullWriteCommand(&receiver);
    }
    void TearDown() override {
        cout.rdbuf(oldCoutStreamBuf);
    }

    TestShellApplication app;
    streambuf* oldCoutStreamBuf;
    ostringstream strCout;
    Receiver receiver;
    FullReadCommand* fullreadCmd;
    FullWriteCommand* fullwriteCmd;
    WriteCommand* writeCmd;

    string expected = "";
    vector<string> v;
};



// Test case for ReadCommand
TEST(CommandTest, ReadCommand) {
    MockReceiver mockReceiver;

    ReadCommand readCommand(&mockReceiver);
    readCommand.execute({"R", "3"});
}

// Test case for WriteCommand
TEST(CommandTest, WriteCommand) {
    MockReceiver mockReceiver;

    WriteCommand writeCommand(&mockReceiver);
    writeCommand.execute({"W", "3", "0x5A5A5A5A"});
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

    EXPECT_FALSE(app.execute(str));
}



TEST_F(TestShellApplicationFixture, FullReadCommandTest) {
    for (int lba = 0; lba < 100; lba++) 
    {
        v = { "write", to_string(lba), "0x12345678"};
        app.executeCommand(writeCmd, v);
    }
    v = { "fullread" };
    app.executeCommand(fullreadCmd, v);
 
    for (int lba = 0; lba < 100; lba++) expected += "0x12345678\n";
    EXPECT_THAT(strCout.str(), testing::Eq(expected));
}


TEST_F(TestShellApplicationFixture, FullWriteCommandTest) {
    v = { "fullwrite", "0x12345678" };
    app.executeCommand(fullwriteCmd, v);
    v = { "fullread" };
    app.executeCommand(fullreadCmd, v);

    for (int lba = 0; lba < 100; lba++) expected += "0x12345678\n";
    EXPECT_THAT(strCout.str(), testing::Eq(expected));
}

TEST_F(TestShellApplicationFixture, TestApp1CommandTest) {
    string str = "testapp1";
    string expected = "0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));

}

TEST_F(TestShellApplicationFixture, TestApp2CommandTest) {
    std::string str = "testapp2";
    string expected = "0x12345678\n0x12345678\n0x12345678\n0x12345678\n0x12345678\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));
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

TEST(ReadCommand, TestExecute) {
    MockReceiver mockReceiver;
    ReadCommand readCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    readCommand.execute({"R", "3"});
    EXPECT_EQ(0, mockReceiver.getResultCode());
}

TEST(WriteCommand, TestExecuteInvalidArgument) {
    MockReceiver mockReceiver;
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({}), invalid_argument);
}

TEST(WriteCommand, TestExecute) {
    MockReceiver mockReceiver;
    WriteCommand writeCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));
        
    writeCommand.execute({ "W", "3", "0xFFF" });
    EXPECT_EQ(0, mockReceiver.getResultCode());

}

TEST(HelpCommand, HelpTestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "help", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST(HelpCommand, HelpTestExecuteInvalidArgumentNo) {
    MockReceiver mockReceiver;
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "3",  };

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST(HelpCommand, HelpTestExecuteInvalidArgumentOver) {
    MockReceiver mockReceiver;
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "full", "3"};

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST(HelpCommand, HelpTestExecutePrintAll) {
    MockReceiver mockReceiver;
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help"};
    helpCommand.execute(args);
    EXPECT_TRUE(true);
}

TEST(HelpCommand, HelpTestExecutePrintOnlyONe) {
    MockReceiver mockReceiver;
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "write"};
    helpCommand.execute(args);
    EXPECT_TRUE(true);
}
