#pragma once
#include "IStorage.h"
#include <stdexcept>
#include <vector>
#include "Buffer.h"

class StorageDriver {
public:
	StorageDriver(IStorage* ssd, Buffer* commandBuffer)
		: ssd(ssd), commandBuffer(commandBuffer)
	{
	}
	void read(int lba)
	{
		commandBuffer->read(lba);
		if (!commandBuffer->BufferHit()) ssd->read(lba);
	}
	void write(int lba, std::string data)
	{
		if (commandBuffer->getBufferSize() >= MAX_BUFFER_SIZE) flush();
		commandBuffer->write(lba, data);
	}
	void erase(int lba, int size)
	{

		if (commandBuffer->getBufferSize() >= MAX_BUFFER_SIZE) flush();
		commandBuffer->erase(lba, size);
	}
	void flush()
	{
		mapbuffer = commandBuffer->flush();
		while (!mapbuffer.empty()) {
			_Buffer bufferdata = mapbuffer.front();
			if (bufferdata.op == 'W') {
				ssd->write(bufferdata.addr, bufferdata.data);
			}
			if (bufferdata.op == 'E') {
				ssd->erase(bufferdata.addr, bufferdata.size);
			}

			mapbuffer.pop();
		}
	}
private:
	IStorage* ssd;
	Buffer* commandBuffer;
	std::queue<_Buffer> mapbuffer;

	const std::string EMPTY = "0x00000000";
	const int MAX_BUFFER_SIZE = 10;
};
