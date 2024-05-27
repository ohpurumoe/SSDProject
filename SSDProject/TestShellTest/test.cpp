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

    MockReceiver mockReceiver;
};

TEST_F(TestShellApplicationFixture, ExitCommandTest) {
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

// ReadCommand
TEST_F(TestShellApplicationFixture, ReadCommandCommandTest) {
    ReadCommand readCommand(&mockReceiver);
    readCommand.execute({ "R", "3" });
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteInvalidArgument) {
    ReadCommand readCommand(&mockReceiver);
    EXPECT_THROW(readCommand.execute({}), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "r", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecute) {
    ReadCommand readCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    readCommand.execute({"R", "3"});
    EXPECT_EQ(0, mockReceiver.getResultCode());
}

// WriteCommand
TEST_F(TestShellApplicationFixture, WriteCommandCommandTest) {
    WriteCommand writeCommand(&mockReceiver);
    writeCommand.execute({ "W", "3", "0x5A5A5A5A" });
}

TEST_F(TestShellApplicationFixture, WriteCommandTestExecuteInvalidArgument) {
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({}), invalid_argument);
}

TEST_F(TestShellApplicationFixture, WriteCommandTestExecute) {
    WriteCommand writeCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));
        
    writeCommand.execute({ "W", "3", "0xFFF" });
    EXPECT_EQ(0, mockReceiver.getResultCode());

}

// HelpCommand
TEST_F(TestShellApplicationFixture, HelpTestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "help", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecuteInvalidArgumentNo) {
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "3",  };

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecuteInvalidArgumentOver) {
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "full", "3"};

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecutePrintAll) {
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help"};

    helpCommand.execute(args);

    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \nexit : Exit this shell\nread : Load data from the LBA ex) read 3\ntestapp2 : Execute test application 2.\nhelp : Display this help message.ex) help write\nfull write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF\nfull read : Perform load data from LBA's all range (0~99) ex) full read\ntestapp1 : Execute test application 1.\n";

    EXPECT_THAT(expected, StrEq(strCout.str()));

}

TEST_F(TestShellApplicationFixture, HelpTestExecutePrintOnlyONe) {
    HelpCommand helpCommand(&mockReceiver);
    vector<string> args = { "help", "write"};

    helpCommand.execute(args);

    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \n";
    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, HelpCommandTest) {
    string str = "help";
    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \nexit : Exit this shell\nread : Load data from the LBA ex) read 3\ntestapp2 : Execute test application 2.\nhelp : Display this help message.ex) help write\nfull write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF\nfull read : Perform load data from LBA's all range (0~99) ex) full read\ntestapp1 : Execute test application 1.\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, HelpCommandExceptionTest) {
    vector<string> v;
    Receiver* receiver = nullptr;

    EXPECT_THROW(app.executeCommand(new HelpCommand(receiver), v), invalid_argument);
}