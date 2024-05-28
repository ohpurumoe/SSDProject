#pragma once
#include "IStorage.h"
#include <stdexcept>
#include <vector>
#include "Buffer.h"
#include "StorageException.h"
#include <regex>

class StorageDriver {
public:
	StorageDriver(IStorage* ssd, Buffer* commandBuffer)
		: ssd(ssd), commandBuffer(commandBuffer)
	{
	}
	void read(int lba)
	{
		validateAddr(lba);

		commandBuffer->read(lba);
		if (!commandBuffer->BufferHit()) ssd->read(lba);
	}
	void write(int lba, std::string data)
	{
		validateAddr(lba);
		validateData(data);

		if (commandBuffer->getBufferSize() >= MAX_BUFFER_SIZE) flush();
		commandBuffer->write(lba, data);
	}
	void erase(int lba, int size)
	{
		validateAddr(lba);
		validateEraseSize(size);

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
	string optimizeCommandBuffer() {
		mapbuffer = commandBuffer->flush();
		vector<_Buffer> temp;

		while (!mapbuffer.empty()) {
			temp.push_back(mapbuffer.front());
			mapbuffer.pop();
		}

		for (int i = 0; i < temp.size(); i++) {
			for (int j = i + 1; j < temp.size(); j++) {
				if (temp[i].op == 'W' && temp[j].op == 'W' && temp[i].addr == temp[j].addr) {
					temp.erase(temp.begin() + i);
				}
			}
		}

		int low, high;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].op == 'E') {
				low = temp[i].addr;
				high = temp[i].addr + temp[i].size;
				for (int j = 0; j < i && j < temp.size(); j++) {
					if (temp[j].op == 'W' && low <= temp[j].addr && temp[j].addr < high) {
						temp.erase(temp.begin() + j);
						j--;
					}
				}
			}
		}

		string ret;
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i].op == 'W') {
				commandBuffer->write(temp[i].addr, temp[i].data);
				ret += "W " + to_string(temp[i].addr) + " " + temp[i].data + "\n";
			}
			else if (temp[i].op == 'E') {
				commandBuffer->erase(temp[i].addr, temp[i].size);
				ret += "E " + to_string(temp[i].addr) + " " + to_string(temp[i].size) + "\n";
			}
		}

		return ret;
	}
private:
	IStorage* ssd;
	Buffer* commandBuffer;
	std::queue<_Buffer> mapbuffer;

	const std::string EMPTY = "0x00000000";
	const int MAX_BUFFER_SIZE = 10;

	void validateEraseSize(const int size) {
		if (size < 1 || 10 < size) {
			throw StorageException("size는 1 ~ 10 사이의 값이어야 합니다. size : " + to_string(size));
		}
	}

	void validateData(const std::string& data)
	{
		regex re("^0x[A-F0-9]{8}");
		if (!regex_match(data, re)) {
			throw StorageException("data는 0x로 시작하고 숫자와 16진수 대문자 8개로 이루어져야합니다. data : " + data);
		}
	}

	void validateAddr(const int LBA)
	{
		if (LBA < 0 || LBA > 99) {
			throw StorageException("LBA는 0 ~ 99 사이의 값이어야 합니다. LBA : " + to_string(LBA));
		}
	}
};
