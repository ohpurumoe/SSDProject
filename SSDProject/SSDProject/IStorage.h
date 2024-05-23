#pragma once
#include <string>

class IStorage {
public:
	virtual int read(int lba) = 0;
	virtual void write(int lba, std::string data) = 0;
};