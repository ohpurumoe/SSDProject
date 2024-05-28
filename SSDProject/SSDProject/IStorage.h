#pragma once
#include <string>
#include <queue>

struct _Buffer {
    char op;
    int addr;
    std::string data;
    int size;
};

class IStorage {
public:
	virtual void read(int lba) = 0;
	virtual void write(int lba, std::string data) = 0;
	virtual void erase(int lba, int size) = 0;
};