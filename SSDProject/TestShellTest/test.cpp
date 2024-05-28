#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../TestShell/Logger.cpp"
#include "../TestShell/ShellRunner.cpp"
#include "../TestShell/InputValidChecker.cpp"
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
    string expected = "INVALID COMMAND, TRY AGAIN\n";

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

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteInvalidArgument) {
    ReadCommand readCommand(&mockReceiver);
    EXPECT_THROW(readCommand.execute({}), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "read", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ReadCommandCommandTest) {
    ReadCommand readCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, read(_))
        .Times(1);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    readCommand.execute({"read", "3"});
    EXPECT_EQ(0, mockReceiver.getResultCode());
}

// WriteCommand
TEST_F(TestShellApplicationFixture, WriteCommandCommandTest) {
    WriteCommand writeCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, write(_))
        .Times(1);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    writeCommand.execute({ "write", "3", "0x5A5A5A5A" });
    EXPECT_THAT(mockReceiver.getResultCode(), 0);
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
        
    writeCommand.execute({ "write", "3", "0xFFFFFFFF" });
    EXPECT_THAT(mockReceiver.getResultCode(), 0);
}

// HelpCommand
TEST_F(TestShellApplicationFixture, HelpTestExecuteNoReceiver) {
    ReadCommand cmd(nullptr);
    vector<string> args = { "help", "3" };
    EXPECT_THROW(cmd.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecuteInvalidArgumentNo) {
    HelpCommand helpCommand(&receiver);
    vector<string> args = { "help", "3",  };

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecuteInvalidArgumentOver) {
    HelpCommand helpCommand(&receiver);
    vector<string> args = { "help", "full", "3"};

    EXPECT_THROW(helpCommand.execute(args), invalid_argument);
}

TEST_F(TestShellApplicationFixture, HelpTestExecutePrintAll) {
    HelpCommand helpCommand(&receiver);
    vector<string> args = { "help"};

    helpCommand.execute(args);

    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \nexit : Exit this shell\nflush : Empty the entire command buffer by executing all commands in the Buffer\nerase : erase [LBA] [SIZE]\nread : Load data from the LBA ex) read 3\nerase_range : erase from [Start LBA] to [End LBA]\nfull write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF\nhelp : Display this help message.ex) help write\nfull read : Perform load data from LBA's all range (0~99) ex) full read\ntestapp1 : Execute test application 1.\ntestapp2 : Execute test application 2.\n";
    EXPECT_THAT(expected, StrEq(strCout.str()));

}

TEST_F(TestShellApplicationFixture, HelpTestExecutePrintOnlyONe) {
    HelpCommand helpCommand(&receiver);
    vector<string> args = { "help", "write"};

    helpCommand.execute(args);

    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \n";
    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, HelpCommandTest) {
    string str = "help";
    string expected = "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB \nexit : Exit this shell\nflush : Empty the entire command buffer by executing all commands in the Buffer\nerase : erase [LBA] [SIZE]\nread : Load data from the LBA ex) read 3\nerase_range : erase from [Start LBA] to [End LBA]\nfull write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF\nhelp : Display this help message.ex) help write\nfull read : Perform load data from LBA's all range (0~99) ex) full read\ntestapp1 : Execute test application 1.\ntestapp2 : Execute test application 2.\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));
}

TEST_F(TestShellApplicationFixture, HelpCommandExceptionTest) {
    vector<string> v;
    Receiver* receiver = nullptr;

    EXPECT_THROW(app.executeCommand(new HelpCommand(receiver), v), invalid_argument);
}

TEST(InputValidChecker, EmptyInput) {
    InputValidChecker checker;
    EXPECT_FALSE(checker.check({}));
}

TEST(InputValidChecker, TestHelpCommand) {
    InputValidChecker checker;
    EXPECT_TRUE(checker.check({ "help" }));
}

TEST(InputValidChecker, TestReadCommand) {
    InputValidChecker checker;
    EXPECT_TRUE(checker.check({ "read", "3" }, InputValidChecker::TYPE_CMD_LBA));
}

TEST(InputValidChecker, TestReadCommandInvalidLBA) {
    InputValidChecker checker;
    EXPECT_FALSE(checker.check({ "read", "A" }, InputValidChecker::TYPE_CMD_LBA));
}

TEST(InputValidChecker, TestWriteCommand) {
    InputValidChecker checker;
    EXPECT_TRUE(checker.check({ "write", "3", "0xAAAABBBB" }, InputValidChecker::TYPE_CMD_LBA_VAL));
}

TEST(InputValidChecker, TestWriteCommandInvalidLBA) {
    InputValidChecker checker;
    EXPECT_FALSE(checker.check({ "write", "3", "FFFF" }, InputValidChecker::TYPE_CMD_LBA_VAL));
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteInvalidInput) {
    ReadCommand readCommand(&mockReceiver);
    EXPECT_THROW(readCommand.execute({ "read", "100" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ReadCommandTestExecuteInvalidInputNum) {
    ReadCommand readCommand(&mockReceiver);
    EXPECT_THROW(readCommand.execute({ "read", "A" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, WriteCommandTestExecuteInvalidInput) {
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({ "write", "3", "FFFF" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, EraseCommandTestExecuteInvalidInput) {
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({ "erase", "3", "FFFF" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, EraseCommandTestExecuteInvalidSize) {
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({ "erase", "3", "11" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, EraseCommandTestExecute) {
    EraseCommand eraseCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, erase(_))
        .Times(1);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    eraseCommand.execute({ "erase", "3", "1" });
    EXPECT_THAT(mockReceiver.getResultCode(), 0);
}

TEST_F(TestShellApplicationFixture, EraseRangeCommandTestExecuteInvalidInput) {
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({ "erase_range", "3", "0xFF" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, EraseRangeCommandTestExecute) {
    EraseCommand eraseCommand(&mockReceiver);

    EXPECT_CALL(mockReceiver, erase(_))
        .Times(1);

    EXPECT_CALL(mockReceiver, getResultCode())
        .Times(1)
        .WillOnce(Return(0));

    eraseCommand.execute({ "erase_range", "3", "5" });
    EXPECT_THAT(mockReceiver.getResultCode(), 0);
}

TEST_F(TestShellApplicationFixture, EraseRangeCommandTestExecuteInvalidNum) {
    Receiver receiver;
    EraseCommand eraseCommand(&mockReceiver);
    EXPECT_THROW(eraseCommand.execute({ "erase_range", "3", "0xFF" }), invalid_argument);
}

TEST_F(TestShellApplicationFixture, ShellRunnerTest) {
    ShellRunner runner(&app);
    string expected = "FullWriteReadCompare --- Run...PASS\nFullRead10AndCompare --- Run...PASS\nWrite10AndCompare --- Run...FAIL\nLoop_WriteAndReadCompare --- Run...FAIL\nUnknown --- Run...FAIL\n";

    string osCmd = "echo FullWriteReadCompare> .\\run_list.lst";
    system(osCmd.c_str());

    osCmd = "echo FullRead10AndCompare>> .\\run_list.lst";
    system(osCmd.c_str());

    osCmd = "echo Write10AndCompare>> .\\run_list.lst";
    system(osCmd.c_str());

    osCmd = "echo Loop_WriteAndReadCompare>> .\\run_list.lst";
    system(osCmd.c_str());

    osCmd = "echo Unknown>> .\\run_list.lst";
    system(osCmd.c_str());

    runner.run(".\\run_list.lst");

    EXPECT_THAT(expected, StrEq(strCout.str()));
}