﻿#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SSDProject/StorageDriver.cpp"
#include "../SSDProject/SSD.cpp"
#include "../SSDProject/Parser.h"
#include "../SSDProject/StorageException.cpp"
#include "../SSDProject/Command.h"
#include <cstring>
#include <utility>

class MockStorage : public IStorage {
public:
	MOCK_METHOD(string, read, (int), (override));
	MOCK_METHOD(void, write, (int, string), (override));
	MOCK_METHOD(void, erase, (int, int), (override));
};

class argsTestFixture: public ::testing::Test{
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

class parseTestFixture: public argsTestFixture{
protected:
	void SetUp() override {
		argsTestFixture::SetUp();
		driver = new StorageDriver(&storage);
		parser = new Parser(driver);
	}
	void TearDown() override {
		argsTestFixture::TearDown();
		delete parser;
		delete driver;
	}

	Parser* parser;
	StorageDriver* driver;
	testing::NiceMock<MockStorage> storage;
};

class commandTestFixture: public argsTestFixture{
protected:
	void SetUp() override {
		argsTestFixture::SetUp();
		driver = new StorageDriver(&storage);
		parser = new Parser(driver);
	}
	void TearDown() override {
		argsTestFixture::TearDown();
		delete parser;
		delete driver;
	}

	Parser* parser;
	StorageDriver* driver;
	testing::NiceMock<MockStorage> storage;
};

TEST_F(parseTestFixture, tooLessArgc){
	cpyArgs(0);
	EXPECT_THROW(parser->parse(0, argv), std::exception);
}

TEST_F(parseTestFixture, wrongArgName){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "WrongArg");
	cpyArgs(2);
	EXPECT_THROW(parser->parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseReadFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	strcpy(argv[3], "wrongArg");
	cpyArgs(4);
	EXPECT_THROW(parser->parse(4, argv), std::exception);
}

TEST_F(parseTestFixture, parseWriteFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_THROW(parser->parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseRead){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	cpyArgs(3);
	auto parsed_pair = parser->parse(3, argv);
	EXPECT_EQ(typeid(*parsed_pair.first), typeid(ReadCommand));
}

TEST_F(parseTestFixture, parseWrite){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	strcpy(argv[3], "0x12345678");
	cpyArgs(4);
	auto parsed_pair = parser->parse(4, argv);
	EXPECT_EQ(typeid(*parsed_pair.first), typeid(WriteCommand));
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
		fRead.close();

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
	ssd.write(13, "0xBBB1BBBB");
	ssd.write(14, "0xCCCCCCCC");
	ssd.write(11, "0xDDDD2DDD");
	ssd.write(12, "0xF5FFFFFF");
	ssd.read(14);

	string  expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDDuplicatedWrite) {
	ssd.write(10, "0xABCDEFAB");
	ssd.write(10, "0xABCDEFBA");
	ssd.read(10);

	string  expected = "0xABCDEFBA";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDReadEmpty) {
	ssd.read(99);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDReadInvalidAddr) {
	EXPECT_THROW(ssd.read(100), StorageException);
	EXPECT_THROW(ssd.read(-1), StorageException);
}

TEST_F(SSDTestFixture, SSDWriteInvalidAddr) {
	EXPECT_THROW(ssd.write(100, "0xFFFFFFFF"), StorageException);
	EXPECT_THROW(ssd.write(-1, "0xFFFFFFFF"), StorageException);
}

TEST_F(SSDTestFixture, SSDWriteInvalidData) {
	EXPECT_THROW(ssd.write(1, "0xABCDEFGH"), StorageException);
}

TEST_F(SSDTestFixture, SSDErase1Addr) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBB1BBBB");
	ssd.write(14, "0xCCCCCCCC");

	ssd.erase(13, 1);

	ssd.read(13);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDErase3Addr) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBB1BBBB");
	ssd.write(14, "0xCCCCCCCC");

	ssd.erase(12, 3);

	string  expected = "0x00000000";
	ssd.read(12);
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
	ssd.read(13);
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
	ssd.read(14);
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, SSDEraseInvalidSize) {
	EXPECT_THROW(ssd.erase(12, 11), StorageException);
}

TEST_F(commandTestFixture, Read) {
	strcpy(argv[1], "R");
	strcpy(argv[2], "0");
	MockStorage storage;
	EXPECT_CALL(storage, read, ::testing::_)
		.Times(1)
		.WillOnce(::testing::Return(""))
		;
	StorageDriver driver(&storage);
	Parser parser(&driver);
	auto cmd_args = parser.parse(3, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
}

TEST_F(commandTestFixture, Write) {
	strcpy(argv[1], "W");
	strcpy(argv[2], "0");
	strcpy(argv[3], "0x12345678");
	MockStorage storage;
	EXPECT_CALL(storage, write, ::testing::_)
		.Times(1)
		;
	StorageDriver driver(&storage);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
}

TEST_F(commandTestFixture, Erase) {
	strcpy(argv[1], "E");
	strcpy(argv[2], "0");
	strcpy(argv[3], "3");
	MockStorage storage;
	EXPECT_CALL(storage, erase, ::testing::_)
		.Times(1)
		;
	StorageDriver driver(&storage);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
}

TEST_F(SSDTestFixture, FlushTest1) {
	StorageDriver driver(&ssd);
	driver.write(1, "0xAAAAAAAA");
	driver.write(2, "0xBBBBBBBB");
	driver.write(3, "0xCCCCCCCC");
	driver.write(4, "0xDDDDDDDD");
	driver.write(5, "0xFFFFFFFF");
	driver.write(6, "0xAAAAAAAA");
	driver.write(7, "0xBBBBBBBB");
	driver.write(8, "0xCCCCCCCC");
	driver.write(9, "0xDDDDDDDD");
	driver.write(10, "0xFFFFFFFF");

	string  expected = "";
	EXPECT_THAT(readResultFile("buffer.txt"), testing::StrEq(expected));
	driver.read(8);
	expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile("result.txt"), testing::StrEq(expected));
}

TEST_F(SSDTestFixture, FlushTest1) {
	StorageDriver driver(&ssd);
	driver.write(7, "0xBBBBBBBB");
	driver.write(8, "0xCCCCCCCC");
	driver.flush();

	string  expected = "";
	EXPECT_THAT(readResultFile("buffer.txt"), testing::StrEq(expected));
	driver.read(8);
	expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile("result.txt"), testing::StrEq(expected));
}