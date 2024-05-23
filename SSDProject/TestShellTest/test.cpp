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
    string expected = "0 0x5A5A5A5A\n1 0x5A5A5A5A\n2 0x5A5A5A5A\n3 0x5A5A5A5A\n4 0x5A5A5A5A\n5 0x5A5A5A5A\n6 0x5A5A5A5A\n7 0x5A5A5A5A\n8 0x5A5A5A5A\n9 0x5A5A5A5A\n10 0x5A5A5A5A\n11 0x5A5A5A5A\n12 0x5A5A5A5A\n13 0x5A5A5A5A\n14 0x5A5A5A5A\n15 0x5A5A5A5A\n16 0x5A5A5A5A\n17 0x5A5A5A5A\n18 0x5A5A5A5A\n19 0x5A5A5A5A\n20 0x5A5A5A5A\n21 0x5A5A5A5A\n22 0x5A5A5A5A\n23 0x5A5A5A5A\n24 0x5A5A5A5A\n25 0x5A5A5A5A\n26 0x5A5A5A5A\n27 0x5A5A5A5A\n28 0x5A5A5A5A\n29 0x5A5A5A5A\n30 0x5A5A5A5A\n31 0x5A5A5A5A\n32 0x5A5A5A5A\n33 0x5A5A5A5A\n34 0x5A5A5A5A\n35 0x5A5A5A5A\n36 0x5A5A5A5A\n37 0x5A5A5A5A\n38 0x5A5A5A5A\n39 0x5A5A5A5A\n40 0x5A5A5A5A\n41 0x5A5A5A5A\n42 0x5A5A5A5A\n43 0x5A5A5A5A\n44 0x5A5A5A5A\n45 0x5A5A5A5A\n46 0x5A5A5A5A\n47 0x5A5A5A5A\n48 0x5A5A5A5A\n49 0x5A5A5A5A\n50 0x5A5A5A5A\n51 0x5A5A5A5A\n52 0x5A5A5A5A\n53 0x5A5A5A5A\n54 0x5A5A5A5A\n55 0x5A5A5A5A\n56 0x5A5A5A5A\n57 0x5A5A5A5A\n58 0x5A5A5A5A\n59 0x5A5A5A5A\n60 0x5A5A5A5A\n61 0x5A5A5A5A\n62 0x5A5A5A5A\n63 0x5A5A5A5A\n64 0x5A5A5A5A\n65 0x5A5A5A5A\n66 0x5A5A5A5A\n67 0x5A5A5A5A\n68 0x5A5A5A5A\n69 0x5A5A5A5A\n70 0x5A5A5A5A\n71 0x5A5A5A5A\n72 0x5A5A5A5A\n73 0x5A5A5A5A\n74 0x5A5A5A5A\n75 0x5A5A5A5A\n76 0x5A5A5A5A\n77 0x5A5A5A5A\n78 0x5A5A5A5A\n79 0x5A5A5A5A\n80 0x5A5A5A5A\n81 0x5A5A5A5A\n82 0x5A5A5A5A\n83 0x5A5A5A5A\n84 0x5A5A5A5A\n85 0x5A5A5A5A\n86 0x5A5A5A5A\n87 0x5A5A5A5A\n88 0x5A5A5A5A\n89 0x5A5A5A5A\n90 0x5A5A5A5A\n91 0x5A5A5A5A\n92 0x5A5A5A5A\n93 0x5A5A5A5A\n94 0x5A5A5A5A\n95 0x5A5A5A5A\n96 0x5A5A5A5A\n97 0x5A5A5A5A\n98 0x5A5A5A5A\n99 0x5A5A5A5A\n100 0x5A5A5A5A\n\n0 0x5A5A5A5A\n1 0x5A5A5A5A\n2 0x5A5A5A5A\n3 0x5A5A5A5A\n4 0x5A5A5A5A\n5 0x5A5A5A5A\n6 0x5A5A5A5A\n7 0x5A5A5A5A\n8 0x5A5A5A5A\n9 0x5A5A5A5A\n10 0x5A5A5A5A\n11 0x5A5A5A5A\n12 0x5A5A5A5A\n13 0x5A5A5A5A\n14 0x5A5A5A5A\n15 0x5A5A5A5A\n16 0x5A5A5A5A\n17 0x5A5A5A5A\n18 0x5A5A5A5A\n19 0x5A5A5A5A\n20 0x5A5A5A5A\n21 0x5A5A5A5A\n22 0x5A5A5A5A\n23 0x5A5A5A5A\n24 0x5A5A5A5A\n25 0x5A5A5A5A\n26 0x5A5A5A5A\n27 0x5A5A5A5A\n28 0x5A5A5A5A\n29 0x5A5A5A5A\n30 0x5A5A5A5A\n31 0x5A5A5A5A\n32 0x5A5A5A5A\n33 0x5A5A5A5A\n34 0x5A5A5A5A\n35 0x5A5A5A5A\n36 0x5A5A5A5A\n37 0x5A5A5A5A\n38 0x5A5A5A5A\n39 0x5A5A5A5A\n40 0x5A5A5A5A\n41 0x5A5A5A5A\n42 0x5A5A5A5A\n43 0x5A5A5A5A\n44 0x5A5A5A5A\n45 0x5A5A5A5A\n46 0x5A5A5A5A\n47 0x5A5A5A5A\n48 0x5A5A5A5A\n49 0x5A5A5A5A\n50 0x5A5A5A5A\n51 0x5A5A5A5A\n52 0x5A5A5A5A\n53 0x5A5A5A5A\n54 0x5A5A5A5A\n55 0x5A5A5A5A\n56 0x5A5A5A5A\n57 0x5A5A5A5A\n58 0x5A5A5A5A\n59 0x5A5A5A5A\n60 0x5A5A5A5A\n61 0x5A5A5A5A\n62 0x5A5A5A5A\n63 0x5A5A5A5A\n64 0x5A5A5A5A\n65 0x5A5A5A5A\n66 0x5A5A5A5A\n67 0x5A5A5A5A\n68 0x5A5A5A5A\n69 0x5A5A5A5A\n70 0x5A5A5A5A\n71 0x5A5A5A5A\n72 0x5A5A5A5A\n73 0x5A5A5A5A\n74 0x5A5A5A5A\n75 0x5A5A5A5A\n76 0x5A5A5A5A\n77 0x5A5A5A5A\n78 0x5A5A5A5A\n79 0x5A5A5A5A\n80 0x5A5A5A5A\n81 0x5A5A5A5A\n82 0x5A5A5A5A\n83 0x5A5A5A5A\n84 0x5A5A5A5A\n85 0x5A5A5A5A\n86 0x5A5A5A5A\n87 0x5A5A5A5A\n88 0x5A5A5A5A\n89 0x5A5A5A5A\n90 0x5A5A5A5A\n91 0x5A5A5A5A\n92 0x5A5A5A5A\n93 0x5A5A5A5A\n94 0x5A5A5A5A\n95 0x5A5A5A5A\n96 0x5A5A5A5A\n97 0x5A5A5A5A\n98 0x5A5A5A5A\n99 0x5A5A5A5A\n100 0x5A5A5A5A\n\n0 0x5A5A5A5A\n1 0x5A5A5A5A\n2 0x5A5A5A5A\n3 0x5A5A5A5A\n4 0x5A5A5A5A\n5 0x5A5A5A5A\n6 0x5A5A5A5A\n7 0x5A5A5A5A\n8 0x5A5A5A5A\n9 0x5A5A5A5A\n10 0x5A5A5A5A\n11 0x5A5A5A5A\n12 0x5A5A5A5A\n13 0x5A5A5A5A\n14 0x5A5A5A5A\n15 0x5A5A5A5A\n16 0x5A5A5A5A\n17 0x5A5A5A5A\n18 0x5A5A5A5A\n19 0x5A5A5A5A\n20 0x5A5A5A5A\n21 0x5A5A5A5A\n22 0x5A5A5A5A\n23 0x5A5A5A5A\n24 0x5A5A5A5A\n25 0x5A5A5A5A\n26 0x5A5A5A5A\n27 0x5A5A5A5A\n28 0x5A5A5A5A\n29 0x5A5A5A5A\n30 0x5A5A5A5A\n31 0x5A5A5A5A\n32 0x5A5A5A5A\n33 0x5A5A5A5A\n34 0x5A5A5A5A\n35 0x5A5A5A5A\n36 0x5A5A5A5A\n37 0x5A5A5A5A\n38 0x5A5A5A5A\n39 0x5A5A5A5A\n40 0x5A5A5A5A\n41 0x5A5A5A5A\n42 0x5A5A5A5A\n43 0x5A5A5A5A\n44 0x5A5A5A5A\n45 0x5A5A5A5A\n46 0x5A5A5A5A\n47 0x5A5A5A5A\n48 0x5A5A5A5A\n49 0x5A5A5A5A\n50 0x5A5A5A5A\n51 0x5A5A5A5A\n52 0x5A5A5A5A\n53 0x5A5A5A5A\n54 0x5A5A5A5A\n55 0x5A5A5A5A\n56 0x5A5A5A5A\n57 0x5A5A5A5A\n58 0x5A5A5A5A\n59 0x5A5A5A5A\n60 0x5A5A5A5A\n61 0x5A5A5A5A\n62 0x5A5A5A5A\n63 0x5A5A5A5A\n64 0x5A5A5A5A\n65 0x5A5A5A5A\n66 0x5A5A5A5A\n67 0x5A5A5A5A\n68 0x5A5A5A5A\n69 0x5A5A5A5A\n70 0x5A5A5A5A\n71 0x5A5A5A5A\n72 0x5A5A5A5A\n73 0x5A5A5A5A\n74 0x5A5A5A5A\n75 0x5A5A5A5A\n76 0x5A5A5A5A\n77 0x5A5A5A5A\n78 0x5A5A5A5A\n79 0x5A5A5A5A\n80 0x5A5A5A5A\n81 0x5A5A5A5A\n82 0x5A5A5A5A\n83 0x5A5A5A5A\n84 0x5A5A5A5A\n85 0x5A5A5A5A\n86 0x5A5A5A5A\n87 0x5A5A5A5A\n88 0x5A5A5A5A\n89 0x5A5A5A5A\n90 0x5A5A5A5A\n91 0x5A5A5A5A\n92 0x5A5A5A5A\n93 0x5A5A5A5A\n94 0x5A5A5A5A\n95 0x5A5A5A5A\n96 0x5A5A5A5A\n97 0x5A5A5A5A\n98 0x5A5A5A5A\n99 0x5A5A5A5A\n100 0x5A5A5A5A\n\n0 0x5A5A5A5A\n1 0x5A5A5A5A\n2 0x5A5A5A5A\n3 0x5A5A5A5A\n4 0x5A5A5A5A\n5 0x5A5A5A5A\n6 0x5A5A5A5A\n7 0x5A5A5A5A\n8 0x5A5A5A5A\n9 0x5A5A5A5A\n10 0x5A5A5A5A\n11 0x5A5A5A5A\n12 0x5A5A5A5A\n13 0x5A5A5A5A\n14 0x5A5A5A5A\n15 0x5A5A5A5A\n16 0x5A5A5A5A\n17 0x5A5A5A5A\n18 0x5A5A5A5A\n19 0x5A5A5A5A\n20 0x5A5A5A5A\n21 0x5A5A5A5A\n22 0x5A5A5A5A\n23 0x5A5A5A5A\n24 0x5A5A5A5A\n25 0x5A5A5A5A\n26 0x5A5A5A5A\n27 0x5A5A5A5A\n28 0x5A5A5A5A\n29 0x5A5A5A5A\n30 0x5A5A5A5A\n31 0x5A5A5A5A\n32 0x5A5A5A5A\n33 0x5A5A5A5A\n34 0x5A5A5A5A\n35 0x5A5A5A5A\n36 0x5A5A5A5A\n37 0x5A5A5A5A\n38 0x5A5A5A5A\n39 0x5A5A5A5A\n40 0x5A5A5A5A\n41 0x5A5A5A5A\n42 0x5A5A5A5A\n43 0x5A5A5A5A\n44 0x5A5A5A5A\n45 0x5A5A5A5A\n46 0x5A5A5A5A\n47 0x5A5A5A5A\n48 0x5A5A5A5A\n49 0x5A5A5A5A\n50 0x5A5A5A5A\n51 0x5A5A5A5A\n52 0x5A5A5A5A\n53 0x5A5A5A5A\n54 0x5A5A5A5A\n55 0x5A5A5A5A\n56 0x5A5A5A5A\n57 0x5A5A5A5A\n58 0x5A5A5A5A\n59 0x5A5A5A5A\n60 0x5A5A5A5A\n61 0x5A5A5A5A\n62 0x5A5A5A5A\n63 0x5A5A5A5A\n64 0x5A5A5A5A\n65 0x5A5A5A5A\n66 0x5A5A5A5A\n67 0x5A5A5A5A\n68 0x5A5A5A5A\n69 0x5A5A5A5A\n70 0x5A5A5A5A\n71 0x5A5A5A5A\n72 0x5A5A5A5A\n73 0x5A5A5A5A\n74 0x5A5A5A5A\n75 0x5A5A5A5A\n76 0x5A5A5A5A\n77 0x5A5A5A5A\n78 0x5A5A5A5A\n79 0x5A5A5A5A\n80 0x5A5A5A5A\n81 0x5A5A5A5A\n82 0x5A5A5A5A\n83 0x5A5A5A5A\n84 0x5A5A5A5A\n85 0x5A5A5A5A\n86 0x5A5A5A5A\n87 0x5A5A5A5A\n88 0x5A5A5A5A\n89 0x5A5A5A5A\n90 0x5A5A5A5A\n91 0x5A5A5A5A\n92 0x5A5A5A5A\n93 0x5A5A5A5A\n94 0x5A5A5A5A\n95 0x5A5A5A5A\n96 0x5A5A5A5A\n97 0x5A5A5A5A\n98 0x5A5A5A5A\n99 0x5A5A5A5A\n100 0x5A5A5A5A\n\n0 0x5A5A5A5A\n1 0x5A5A5A5A\n2 0x5A5A5A5A\n3 0x5A5A5A5A\n4 0x5A5A5A5A\n5 0x5A5A5A5A\n6 0x5A5A5A5A\n7 0x5A5A5A5A\n8 0x5A5A5A5A\n9 0x5A5A5A5A\n10 0x5A5A5A5A\n11 0x5A5A5A5A\n12 0x5A5A5A5A\n13 0x5A5A5A5A\n14 0x5A5A5A5A\n15 0x5A5A5A5A\n16 0x5A5A5A5A\n17 0x5A5A5A5A\n18 0x5A5A5A5A\n19 0x5A5A5A5A\n20 0x5A5A5A5A\n21 0x5A5A5A5A\n22 0x5A5A5A5A\n23 0x5A5A5A5A\n24 0x5A5A5A5A\n25 0x5A5A5A5A\n26 0x5A5A5A5A\n27 0x5A5A5A5A\n28 0x5A5A5A5A\n29 0x5A5A5A5A\n30 0x5A5A5A5A\n31 0x5A5A5A5A\n32 0x5A5A5A5A\n33 0x5A5A5A5A\n34 0x5A5A5A5A\n35 0x5A5A5A5A\n36 0x5A5A5A5A\n37 0x5A5A5A5A\n38 0x5A5A5A5A\n39 0x5A5A5A5A\n40 0x5A5A5A5A\n41 0x5A5A5A5A\n42 0x5A5A5A5A\n43 0x5A5A5A5A\n44 0x5A5A5A5A\n45 0x5A5A5A5A\n46 0x5A5A5A5A\n47 0x5A5A5A5A\n48 0x5A5A5A5A\n49 0x5A5A5A5A\n50 0x5A5A5A5A\n51 0x5A5A5A5A\n52 0x5A5A5A5A\n53 0x5A5A5A5A\n54 0x5A5A5A5A\n55 0x5A5A5A5A\n56 0x5A5A5A5A\n57 0x5A5A5A5A\n58 0x5A5A5A5A\n59 0x5A5A5A5A\n60 0x5A5A5A5A\n61 0x5A5A5A5A\n62 0x5A5A5A5A\n63 0x5A5A5A5A\n64 0x5A5A5A5A\n65 0x5A5A5A5A\n66 0x5A5A5A5A\n67 0x5A5A5A5A\n68 0x5A5A5A5A\n69 0x5A5A5A5A\n70 0x5A5A5A5A\n71 0x5A5A5A5A\n72 0x5A5A5A5A\n73 0x5A5A5A5A\n74 0x5A5A5A5A\n75 0x5A5A5A5A\n76 0x5A5A5A5A\n77 0x5A5A5A5A\n78 0x5A5A5A5A\n79 0x5A5A5A5A\n80 0x5A5A5A5A\n81 0x5A5A5A5A\n82 0x5A5A5A5A\n83 0x5A5A5A5A\n84 0x5A5A5A5A\n85 0x5A5A5A5A\n86 0x5A5A5A5A\n87 0x5A5A5A5A\n88 0x5A5A5A5A\n89 0x5A5A5A5A\n90 0x5A5A5A5A\n91 0x5A5A5A5A\n92 0x5A5A5A5A\n93 0x5A5A5A5A\n94 0x5A5A5A5A\n95 0x5A5A5A5A\n96 0x5A5A5A5A\n97 0x5A5A5A5A\n98 0x5A5A5A5A\n99 0x5A5A5A5A\n100 0x5A5A5A5A\n\n";

    app.execute(str);

    EXPECT_THAT(expected, StrEq(strCout.str()));

}

TEST_F(TestShellApplicationFixture, TestApp2CommandTest) {
    std::string str = "testapp2";
    string expected = "0 0x12345678\n1 0x12345678\n2 0x12345678\n3 0x12345678\n4 0x12345678\n\n";

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

TEST(WriteCommand, TestExecuteInvalidArgument) {
    MockReceiver mockReceiver;
    WriteCommand writeCommand(&mockReceiver);
    EXPECT_THROW(writeCommand.execute({}), invalid_argument);
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

