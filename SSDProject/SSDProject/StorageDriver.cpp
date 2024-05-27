#pragma once
#include "IStorage.h"
#include <stdexcept>
#include <vector>

class StorageDriver {
public:
	StorageDriver(IStorage* ssd/*, IStorage* commandBuffer*/)
		: ssd(ssd)//, commandBuffer(commandBuffer)
	{
	}
	void read(int lba)
	{
		//if(commandBuffer->read(lba) == EMPTY) 
		ssd->read(lba);
	}
	void write(int lba, std::string data)
	{
		//if(commandBuffer->write(lba, data) == MAX_BUFFER_SIZE) flush();
		ssd->write(lba, data);
	}
	void erase(int lba, int size)
	{

		//if(commandBuffer->erase(lba, size) == MAX_BUFFER_SIZE) flush();
		ssd->erase(lba, size);
	}
	void flush()
	{
		//mapbuffer = commandBuffer->flush();
		//while (mapbuffer.empty()) {
		//	_Buffer bufferdata = mapbuffer.front();
		//	if (bufferdata.op == 'W') {
		//		ssd->write(bufferdata.addr, bufferdata.data);
		//	}
		//	if (bufferdata.op == 'E') {
		//		ssd->erase(bufferdata.addr, bufferdata.size);
		//	}

		//	mapbuffer.pop();
		//}
	}
private:
	IStorage* ssd;
	IStorage* commandBuffer;
	std::queue<_Buffer> mapbuffer;

	const std::string EMPTY = "0x00000000";
	const int MAX_BUFFER_SIZE = 10;
};
