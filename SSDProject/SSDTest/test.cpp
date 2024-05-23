#include <cstring>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SSDProject/StorageDriver.cpp"
#include "../SSDProject/util.h"

class parseTestFixture: public ::testing::Test{
protected:
	void SetUp() override {
		argv = new char*[4];
		for(int i = 0; i < 4; ++i){
			argv[i] = new char[50];
			memset(argv[i], '\0', 50 * sizeof(char));
		}
	}
	void TearDown() override {
		for(int i = 0; i < 4; ++i){
			delete[] argv[i];
		}
		delete[] argv;
	}

	char** argv;
};

TEST_F(parseTestFixture, tooLessArgc){
	EXPECT_THROW(parse(0, argv), std::exception);
}

TEST_F(parseTestFixture, wrongCmdName){
	strcpy(argv[0], "wrongCmd");
	EXPECT_THROW(parse(1, argv), std::exception);
}

TEST_F(parseTestFixture, wrongArgName){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "WrongArg");
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseReadFail){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	strcpy(argv[3], "wrongArg");
	EXPECT_THROW(parse(4, argv), std::exception);
}

TEST_F(parseTestFixture, parseWriteFail){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseRead){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	EXPECT_EQ(parse(3, argv), Command::READ);
}

TEST_F(parseTestFixture, parseWrite){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	strcpy(argv[3], "0x12345678");
	EXPECT_EQ(parse(4, argv), Command::WRITE);
}