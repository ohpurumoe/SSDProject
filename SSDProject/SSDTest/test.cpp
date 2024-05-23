﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SSDProject/StorageDriver.cpp"
#include "../SSDProject/SSD.cpp"
#include "../SSDProject/util.h"
#include <cstring>

class parseTestFixture: public ::testing::Test{
protected:
	void SetUp() override {
		argv = new char*[4];
		for(int i = 0; i < 4; ++i){
			argv[i] = new char[50];
			memset(argv[i], '\0', 50 * sizeof(char));
		}
	}
	void cpyArgs(int argc) {
		for(int i = 2; i < argc; ++i){
			args.push_back(argv[i]);
		}
	}
	void TearDown() override {
		for(int i = 0; i < 4; ++i){
			delete[] argv[i];
		}
		delete[] argv;
	}

	char** argv;
	std::vector<std::string> args;
};

TEST_F(parseTestFixture, tooLessArgc){
	cpyArgs(0);
	EXPECT_THROW(parse(0, argv), std::exception);
}

TEST_F(parseTestFixture, wrongArgName){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "WrongArg");
	cpyArgs(2);
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseReadFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	strcpy(argv[3], "wrongArg");
	cpyArgs(4);
	EXPECT_THROW(parse(4, argv), std::exception);
}

TEST_F(parseTestFixture, parseWriteFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseRead){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_EQ(parse(3, argv), std::make_pair(Command::READ, args));
}

TEST_F(parseTestFixture, parseWrite){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	strcpy(argv[3], "0x12345678");
	cpyArgs(4);
	EXPECT_EQ(parse(4, argv), std::make_pair(Command::WRITE, args));
}

class SSDTestFixture : public ::testing::Test {
protected:
	void SetUp() override {
	}
	void TearDown() override {
	}
	string readResultFile(string filename = "result.txt") {
		fRead.open(filename);
		string readResult;
		getline(fRead, readResult);

		return readResult;
	}
public:
	SSD ssd;
private:
	ifstream fRead;
};

TEST_F(SSDTestFixture, SSDRWSuccess1) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.read(12);

	string  expected = "0xAAAAAAAA";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDRWSuccess2) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBBBBBBB");
	ssd.write(14, "0xCCCCCCCC");
	ssd.write(11, "0xDDDDDDDD");
	ssd.write(12, "0xFFFFFFFF");
	ssd.read(12);

	string  expected = "0xFFFFFFFF";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDRWSuccess3) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBBBBBBB");
	ssd.write(14, "0xCCCCCCCC");
	ssd.write(11, "0xDDDDDDDD");
	ssd.write(12, "0xFFFFFFFF");
	ssd.read(14);

	string  expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDDuplicatedWrite) {
	ssd.write(10, "0xABCDEFGH");
	ssd.write(10, "0xABCDEFGA");
	ssd.read(10);

	string  expected = "0xABCDEFGA";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDReadEmpty) {
	ssd.read(99);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

class MockStorage : public IStorage {
public:
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(void, write, (int, string), (override));
};

TEST(Execute, Read) {
	MockStorage storage;
	EXPECT_CALL(storage, read, ::testing::_)
		.Times(1)
		.WillOnce(::testing::Return(""))
		;
	StorageDriver driver(&storage);
	CommandArgsPair cmd_args = { Command::READ, {"0"} };
	execute(driver, cmd_args);
}

TEST(Execute, Write) {
	MockStorage storage;
	EXPECT_CALL(storage, write, ::testing::_)
		.Times(1)
		;
	StorageDriver driver(&storage);
	CommandArgsPair cmd_args = { Command::WRITE, {"0", "0x12345678"}};
	execute(driver, cmd_args);
}
