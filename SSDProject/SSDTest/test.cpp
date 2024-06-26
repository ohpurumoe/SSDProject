﻿#define _CRT_SECURE_NO_WARNINGS
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SSDProject/SSD.cpp"
#include "../SSDProject/Parser.h"
#include "../SSDProject/StorageException.cpp"
#include <cstring>
#include "../SSDProject/Buffer.cpp"
#include <utility>

class MockStorage : public IStorage {
public:
	MOCK_METHOD(void, read, (int), (override));
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
		driver = new StorageDriver(&storage, &CommandBuffer);
		parser = new Parser(driver);
	}
	void TearDown() override {
		argsTestFixture::TearDown();
		delete parser;
		delete driver;
	}

	Parser* parser;
	StorageDriver* driver;
	Buffer CommandBuffer;
	testing::NiceMock<MockStorage> storage;
};

class commandTestFixture: public argsTestFixture{
protected:
	void SetUp() override {
		argsTestFixture::SetUp();
		driver = new StorageDriver(&storage, &CommandBuffer);
		realDriver = new StorageDriver(&ssd, &CommandBuffer);
		parser = new Parser(driver);
		CommandBuffer.flush();
	}
	void TearDown() override {
		argsTestFixture::TearDown();
		delete parser;
		delete driver;
		delete realDriver;
	}
	string readResultFile(string filename = "result.txt") {
		fRead.open(filename);
		string readResult;
		getline(fRead, readResult);
		fRead.close();

		return readResult;
	}
	ifstream fRead;
	Parser* parser;
	StorageDriver* driver;
	StorageDriver* realDriver;
	SSD ssd;
	Buffer CommandBuffer;
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

TEST_F(parseTestFixture, parseEraseFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "E");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_THROW(parser->parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseFlushFail){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "F");
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

TEST_F(parseTestFixture, parseErase){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "E");
	strcpy(argv[2], "5");
	strcpy(argv[3], "5");
	cpyArgs(4);
	auto parsed_pair = parser->parse(4, argv);
	EXPECT_EQ(typeid(*parsed_pair.first), typeid(EraseCommand));
}

TEST_F(parseTestFixture, parseFlush){
	strcpy(argv[0], "SSD.exe");
	strcpy(argv[1], "F");
	cpyArgs(2);
	auto parsed_pair = parser->parse(2, argv);
	EXPECT_EQ(typeid(*parsed_pair.first), typeid(FlushCommand));
}

TEST_F(commandTestFixture, SSDRWSuccess1) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.read(12);

	string  expected = "0xAAAAAAAA";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDRWSuccess2) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBBBBBBB");
	ssd.write(14, "0xCCCCCCCC");
	ssd.write(11, "0xDDDDDDDD");
	ssd.write(12, "0xFFFFFFFF");
	ssd.read(12);

	string  expected = "0xFFFFFFFF";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDRWSuccess3) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBB1BBBB");
	ssd.write(14, "0xCCCCCCCC");
	ssd.write(11, "0xDDDD2DDD");
	ssd.write(12, "0xF5FFFFFF");
	ssd.read(14);

	string  expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDDuplicatedWrite) {
	ssd.write(10, "0xABCDEFAB");
	ssd.write(10, "0xABCDEFBA");
	ssd.read(10);

	string  expected = "0xABCDEFBA";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDReadEmpty) {
	ssd.read(99);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDErase1Addr) {
	ssd.write(12, "0xAAAAAAAA");
	ssd.write(13, "0xBBB1BBBB");
	ssd.write(14, "0xCCCCCCCC");

	ssd.erase(13, 1);

	ssd.read(13);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, SSDErase3Addr) {
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

TEST_F(commandTestFixture, BufferRWSuccess) {
	CommandBuffer.write(10, "0xABCDEFAB");
	CommandBuffer.read(10);

	string  expected = "0xABCDEFAB";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferRWSuccess2) {
	CommandBuffer.write(10, "0xABCDEFAB");
	CommandBuffer.write(12, "0xABCAEFAB");
	CommandBuffer.write(14, "0xAB2DEFAB");
	CommandBuffer.write(11, "0xAB2DEF5B");
	CommandBuffer.write(5, "0xAB2DE35B");
	CommandBuffer.read(14);

	string  expected = "0xAB2DEFAB";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferRWOverwrite) {
	CommandBuffer.write(10, "0xABCDEFAB");
	CommandBuffer.write(12, "0xABCAEFAB");
	CommandBuffer.write(14, "0xAB2DEFAB");
	CommandBuffer.write(11, "0xAB2DEF5B");
	CommandBuffer.write(5, "0xAB2DE35B");
	CommandBuffer.write(14, "0xAB2DEFEB");
	CommandBuffer.read(14);

	string  expected = "0xAB2DEFEB";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferErase) {
	CommandBuffer.write(5, "0xAB2DE35B");
	CommandBuffer.erase(5, 1);
	CommandBuffer.read(5);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferBlockErase) {
	CommandBuffer.write(10, "0xABCDEFAB");
	CommandBuffer.write(11, "0xABCAEFAB");
	CommandBuffer.write(12, "0xAB2DEFAB");
	CommandBuffer.write(13, "0xAB2DEF5B");
	CommandBuffer.write(14, "0xAB2DE35B");
	CommandBuffer.erase(10, 3);
	CommandBuffer.read(12);

	string  expected = "0x00000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferFlush) {
	CommandBuffer.write(5, "0xAB2DE35B");
	CommandBuffer.flush();
	CommandBuffer.read(5);

	string  expected = "0000000000";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, BufferFull) {
	CommandBuffer.write(1, "0xAB2DE35B");
	CommandBuffer.write(2, "0xAB2DE35B");
	CommandBuffer.write(3, "0xAB2DE35B");
	CommandBuffer.write(4, "0xAB2DE35B");
	CommandBuffer.write(5, "0xAB2DE35B");
	CommandBuffer.write(6, "0xAB2DE35B");
	CommandBuffer.write(7, "0xAB2DE35B");
	CommandBuffer.write(8, "0xAB2DE35B");
	CommandBuffer.write(9, "0xAB2DE35B");
	CommandBuffer.write(10, "0xAB2DE35B");
	
	EXPECT_THROW(CommandBuffer.write(11, "0xAB2DE35B"), StorageException);
}

TEST_F(commandTestFixture, Read) {
	strcpy(argv[1], "R");
	strcpy(argv[2], "0");
	MockStorage storage;
	Buffer CommandBuffer;
	EXPECT_CALL(storage, read)
		.Times(1)
		;

	StorageDriver driver(&storage, &CommandBuffer);
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
	Buffer CommandBuffer;
	EXPECT_CALL(storage, write)
		.Times(1)
		;
	StorageDriver driver(&storage, &CommandBuffer);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
	driver.flush();
}

TEST_F(commandTestFixture, Erase) {
	strcpy(argv[1], "E");
	strcpy(argv[2], "0");
	strcpy(argv[3], "3");
	MockStorage storage;
	Buffer CommandBuffer;
	EXPECT_CALL(storage, erase)
		.Times(1)
		;
	StorageDriver driver(&storage, &CommandBuffer);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
	driver.flush();
}

TEST_F(commandTestFixture, Flush) {
	strcpy(argv[1], "E");
	strcpy(argv[2], "0");
	strcpy(argv[3], "3");
	MockStorage storage;
	Buffer CommandBuffer;
	EXPECT_CALL(storage, erase)
		.Times(1)
		;
	StorageDriver driver(&storage, &CommandBuffer);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);
	strcpy(argv[1], "F");
	cmd_args = parser.parse(2, argv);
	cmd = cmd_args.first;
	args = cmd_args.second;
	cmd->execute(args);
}

TEST_F(commandTestFixture, ReadWrite) {
	strcpy(argv[1], "W");
	strcpy(argv[2], "0");
	strcpy(argv[3], "0x12345678");
	SSD storage;
	Buffer CommandBuffer;

	StorageDriver driver(&storage, &CommandBuffer);
	Parser parser(&driver);
	auto cmd_args = parser.parse(4, argv);
	auto& cmd = cmd_args.first;
	auto& args = cmd_args.second;
	cmd->execute(args);

	strcpy(argv[1], "R");
	strcpy(argv[2], "0");

	cmd_args = parser.parse(3, argv);
	cmd = cmd_args.first;
	args = cmd_args.second;
	cmd->execute(args);
	std::string expected = "0x12345678";
	EXPECT_THAT(readResultFile(), testing::StrEq(expected));

}

TEST_F(commandTestFixture, StorageReadInvalidAddr) {
	EXPECT_THROW(driver->read(100), StorageException);
	EXPECT_THROW(driver->read(-1), StorageException);
}

TEST_F(commandTestFixture, StorageWriteInvalidAddr) {
	EXPECT_THROW(driver->write(100, "0xFFFFFFFF"), StorageException);
	EXPECT_THROW(driver->write(-1, "0xFFFFFFFF"), StorageException);
}

TEST_F(commandTestFixture, StorageWriteInvalidData) {
	EXPECT_THROW(driver->write(1, "0xABCDEFGH"), StorageException);
}

TEST_F(commandTestFixture, StorageEraseInvalidSize) {
	EXPECT_THROW(driver->erase(12, 11), StorageException);
}

TEST_F(commandTestFixture, StorageFlushTest1) {
	realDriver->write(1, "0xAAAAAAAA");
	realDriver->write(2, "0xBBBBBBBB");
	realDriver->write(3, "0xCCCCCCCC");
	realDriver->write(4, "0xDDDDDDDD");
	realDriver->write(5, "0xFFFFFFFF");
	realDriver->write(6, "0xAAAAAAAA");
	realDriver->write(7, "0xBBBBBBBB");
	realDriver->write(8, "0xCCCCCCCC");
	realDriver->write(9, "0xDDDDDDDD");
	realDriver->write(10, "0xFFFFFFFF");
	realDriver->write(11, "0xFFFFFFFF");
	realDriver->write(12, "0xFFFFFFFF");

	realDriver->read(1);
	string  expected = "0xAAAAAAAA";
	EXPECT_THAT(readResultFile("result.txt"), testing::StrEq(expected));
}

TEST_F(commandTestFixture, StorageFlushTest2) {
	realDriver->write(7, "0xBBBBBBBB");
	realDriver->write(8, "0xCCCCCCCC");
	realDriver->flush();

	string  expected = "";
	EXPECT_THAT(readResultFile("buffer.txt"), testing::StrEq(expected));
	realDriver->read(8);
	expected = "0xCCCCCCCC";
	EXPECT_THAT(readResultFile("result.txt"), testing::StrEq(expected));
}

TEST_F(commandTestFixture, StorageCommandBufferOptimize1) {
	driver->write(20, "0xABCDABCD");
	driver->write(21, "0x12341234");
	driver->write(20, "0xEEEEFFFF");

	string expected = "W 21 0x12341234\nW 20 0xEEEEFFFF\n";
	EXPECT_THAT(driver->optimizeCommandBuffer(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, StorageCommandBufferOptimize2) {
	driver->write(20, "0xABCDABCD");
	driver->write(21, "0x12341234");
	driver->erase(18, 5);

	string expected = "E 18 5\n";
	EXPECT_THAT(driver->optimizeCommandBuffer(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, StorageCommandBufferOptimize3) {
	driver->write(20, "0xABCDABCD");
	driver->erase(10, 2);
	driver->erase(12, 3);

	string expected = "W 20 0xABCDABCD\nE 10 5\n";
	EXPECT_THAT(driver->optimizeCommandBuffer(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, DISABLED_StorageCommandBufferOptimize4) {

	driver->erase(10, 4);
	driver->erase(40, 5);
	driver->write(12, "0xABCD1234");
	driver->write(12, "0xABCD1234");

	string expected = "E 10 2\nE 40 5\nW 12 0xABCD1234\n13 0x4BCD5351\n";
	EXPECT_THAT(driver->optimizeCommandBuffer(), testing::StrEq(expected));

	driver->erase(50, 1);
	driver->erase(40, 5);
	driver->write(50, "0xABCD1234");

	expected = "E 40 5\nW 50 0xABCD1234\n";
	EXPECT_THAT(driver->optimizeCommandBuffer(), testing::StrEq(expected));
}

TEST_F(commandTestFixture, StorageCommandBufferOptimize5) {
	driver->erase(10, 2);
	driver->write(10, "0xABCDABCD");
	driver->erase(12, 3);

	string expected = "W 10 0xABCDABCD\nE 11 4\n";
	EXPECT_THAT(driver->optimizeCommandBuffer5(), testing::StrEq(expected));
}