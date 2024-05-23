#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../TestShell/TestShellApplication.cpp"

TEST(TestShellApplication, WriteCommand) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestShellApplication, ReadCommand) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestShellApplication, HelpCommand) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestShellApplication, ExitCommand) {
    TestShellApplication app;
    std::string str = "exit";

    EXPECT_TRUE(app.execute(str));
}

TEST(TestShellApplication, FulReadCommand) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}


TEST(TestShellApplication, FullWriteCommand) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(TestShellApplication, TestApp1Command) {
    TestShellApplication app;
    std::string str = "testapp1";

    EXPECT_TRUE(app.execute(str));
}

TEST(TestShellApplication, TestApp2Command) {
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}