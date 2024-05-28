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
		vector<_Buffer> Commands;

		CopyBufferToVector(Commands);

		OptimizeOverwrite(Commands);
		OptimizeEraseAfterWrite(Commands);
		OptimizeEraseTwice(Commands);

		return ProcessOptimizedCommand(Commands);
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

	void CopyBufferToVector(vector<_Buffer>& commands)
	{
		while (!mapbuffer.empty()) {
			commands.push_back(mapbuffer.front());
			mapbuffer.pop();
		}
	}

	void OptimizeOverwrite(vector<_Buffer>& commands)
	{
		for (int i = 0; i < commands.size(); i++) {
			for (int j = i + 1; j < commands.size(); j++) {
				if (commands[i].op == 'W' && commands[j].op == 'W' && commands[i].addr == commands[j].addr) {
					commands.erase(commands.begin() + i);
				}
			}
		}
	}

	void OptimizeEraseAfterWrite(vector<_Buffer>& commands)
	{
		int low, high;
		for (int i = 0; i < commands.size(); i++) {
			if (commands[i].op != 'E') continue;

			low = commands[i].addr;
			high = commands[i].addr + commands[i].size;
			for (int j = 0; j < i && j < commands.size(); j++) {
				if (commands[j].op == 'W' && low <= commands[j].addr && commands[j].addr < high) {
					commands.erase(commands.begin() + j);
					j--;
				}
			}
		}
	}

	void OptimizeEraseTwice(vector<_Buffer>& commands)
	{
		for (int i = 0; i < commands.size() - 1; ++i) {
			if (commands[i].op == 'E' && commands[i + 1].op == 'E' &&
				commands[i].addr + commands[i].size == commands[i + 1].addr &&
				commands[i].size <= 10 && commands[i + 1].size <= 10) {
				// 두 개의 Erase 명령어를 합침
				commands[i].size += commands[i + 1].size;
				commands.erase(commands.begin() + i + 1);
			}
		}
	}

	string ProcessOptimizedCommand(vector<_Buffer>& commands)
	{
		string ret;

		for (int i = 0; i < commands.size(); i++) {
			if (commands[i].op == 'W') {
				commandBuffer->write(commands[i].addr, commands[i].data);
				ret += "W " + to_string(commands[i].addr) + " " + commands[i].data + "\n";
			}
			else if (commands[i].op == 'E') {
				commandBuffer->erase(commands[i].addr, commands[i].size);
				ret += "E " + to_string(commands[i].addr) + " " + to_string(commands[i].size) + "\n";
			}
		}

		return ret;
	}
};
