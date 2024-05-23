#pragma once
#include "IStorage.h"

class StorageDriver {
public:
	StorageDriver(IStorage* ssd)
		: ssd(ssd)
	{
	}
	int read(int lba)
	{
		return ssd->read(lba);
	}
	void write(int lba, std::string data)
	{
		ssd->write(lba, data);
	}
private:
	IStorage* ssd;
};