#include "IStorage.h"

class StorageDriver {
public:
	StorageDriver(IStorage* ssd)
		: ssd(ssd)
	{
	}
	int read(int lba)
	{
		ssd->read(lba);
	}
	void write(int lba, int data)
	{
		ssd->write(lba, data);
	}
private:
	IStorage* ssd;
};