#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../SSDProject/StorageDriver.cpp"
#include "../SSDProject/SSD.cpp"


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