#include "gmock/gmock.h"
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
		for(int i = 1; i < argc; ++i){
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

TEST_F(parseTestFixture, wrongCmdName){
	strcpy(argv[0], "wrongCmd");
	cpyArgs(1);
	EXPECT_THROW(parse(1, argv), std::exception);
}

TEST_F(parseTestFixture, wrongArgName){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "WrongArg");
	cpyArgs(2);
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseReadFail){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	strcpy(argv[3], "wrongArg");
	cpyArgs(4);
	EXPECT_THROW(parse(4, argv), std::exception);
}

TEST_F(parseTestFixture, parseWriteFail){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_THROW(parse(3, argv), std::exception);
}

TEST_F(parseTestFixture, parseRead){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "R");
	strcpy(argv[2], "5");
	cpyArgs(3);
	EXPECT_EQ(parse(3, argv), std::make_pair(Command::READ, args));
}

TEST_F(parseTestFixture, parseWrite){
	strcpy(argv[0], "ssd");
	strcpy(argv[1], "W");
	strcpy(argv[2], "5");
	strcpy(argv[3], "0x12345678");
	cpyArgs(4);
	EXPECT_EQ(parse(4, argv), std::make_pair(Command::WRITE, args));
}

TEST(SSDTest, StorageDriverTest) {
	EXPECT_EQ(1, 1);
}

TEST(SSDTest, SSDWriteSuccess) {
	SSD ssd;

	ssd.open();
	ssd.write(1, "0xABCDEFGH");
	ssd.close();
}

TEST(SSDTest, SSDReadSuccess) {

}

class MockStorage : public IStorage {
public:
	MOCK_METHOD(int, read, (int), (override));
	MOCK_METHOD(void, write, (int, string), (override));
};

TEST(Execute, Read) {
	MockStorage storage;
	EXPECT_CALL(storage, read, ::testing::_)
		.Times(1)
		.WillOnce(::testing::Return(0))
		;
	StorageDriver driver(&storage);
	CommandArgsPair cmd_args;
	execute(driver, cmd_args);
}