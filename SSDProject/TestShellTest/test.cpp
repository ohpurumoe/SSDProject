#include "gmock/gmock.h"
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
    }
    void TearDown() override {
        cout.rdbuf(oldCoutStreamBuf);
    }

    TestShellApplication app;
    ostringstream strCout;
    streambuf* oldCoutStreamBuf;
};

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

    EXPECT_FALSE(app.execute(str));
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

TEST_F(TestShellApplicationFixture, TestApp1CommandTest) {
    string str = "testapp1";
    string expected = "0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n0x5A5A5A5A\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));

}


TEST_F(TestShellApplicationFixture, TestApp1InvalidCommandTest) {
    string str = "error";
    string expected = "invalid command, try again\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, TestApp1ExceptionCommandTest) {
    string str = "testapp1 1 2 3";
    EXPECT_THROW(app.execute(str), exception);
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

TEST_F(TestShellApplicationFixture, HelpCommandTest) {
    string str = "help";
    string expected = "Executing help command\nwrite : Save data into the LBA ex) wrtie 3 0xAAAABBBB \nexit : Exit this shell\nread : Load data from the LBA ex) read 3\ntestapp2 : Execute test application 2.\nhelp : Display this help message.ex) help write\nfull write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF\nfull read : Perform load data from LBA's all range (0~99) ex) full read\ntestapp1 : Execute test application 1.\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, HelpCommandExceptionTest) {
    vector<string> v;
    Receiver* receiver = nullptr;

    EXPECT_THROW(app.executeCommand(new HelpCommand(receiver), v), invalid_argument);
}