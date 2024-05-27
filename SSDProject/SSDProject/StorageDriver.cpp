#pragma once
#include "IStorage.h"
#include <stdexcept>
#include <vector>

class StorageDriver {
public:
	StorageDriver(IStorage* ssd)
		: ssd(ssd)
	{
	}
	void read(int lba)
	{
		ssd->read(lba);
	}
	void write(int lba, std::string data)
	{
		ssd->write(lba, data);
	}
	void erase(int lba, int size)
	{
		ssd->erase(lba, size);
	}

private:
	IStorage* ssd;
};
