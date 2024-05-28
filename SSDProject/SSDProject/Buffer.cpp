#include "Buffer.h"

std::string Buffer::read(int lba)
{
	fillBuffer();

	_Buffer retBuffer, tempBuffer;
	while (!qBuffer.empty()) {
		tempBuffer = qBuffer.front();
		if (tempBuffer.addr == lba) {
			if (tempBuffer.op == 'W')
				retBuffer.data = tempBuffer.data;
			else if (tempBuffer.op == 'E')
				retBuffer.data = "0x00000000";
		}
		qBuffer.pop();
	}

	return retBuffer.data;
}

void Buffer::write(int lba, std::string data)
{
	queueBuffer('W', lba, 0, data);
	storeBuffer();
}

void Buffer::erase(int lba, int size)
{
	queueBuffer('E', lba, size, "0x00000000");
	storeBuffer();
}

queue<_Buffer> Buffer::flush() {
	queue <_Buffer> retBuffer = qBuffer;

	clearBuffer();

	return retBuffer;
}

int Buffer::getBufferSize() {
	return (int)qBuffer.size();
}

void Buffer::fillBuffer() {
	_Buffer tempBuffer;

	clearBuffer();

	fBufferIn.open(filename);
	string line;
	while (getline(fBufferIn, line)) {
		if (line.size() == 0) continue;

		char* pPos = (char*)line.c_str();
		char* pPos2 = nullptr;
		pPos = strtok_s(pPos, " ", &pPos2);
		tempBuffer.op = line[0];
		pPos = strtok_s(nullptr, " ", &pPos2);
		tempBuffer.addr = stoi(pPos);
		pPos = strtok_s(nullptr, " ", &pPos2);
		tempBuffer.size = stoi(pPos);
		pPos = strtok_s(nullptr, " ", &pPos2);
		tempBuffer.data = pPos;

		qBuffer.push(tempBuffer);
	}
	fBufferIn.close();
}

void Buffer::queueBuffer(char op, int lba, int size, string data) {
	fillBuffer();

	_Buffer tempBuffer;

	tempBuffer.op = op;
	tempBuffer.addr = lba;
	tempBuffer.size = size;
	tempBuffer.data = data;
	qBuffer.push(tempBuffer);
}

void Buffer::clearBuffer()
{
	while (!qBuffer.empty())
		qBuffer.pop();
}

void Buffer::storeBuffer() {
	_Buffer tempBuffer;
	fBufferOut.open(filename, ios::out | ios::trunc);
	while (!qBuffer.empty()) {
		tempBuffer = qBuffer.front();
		fBufferOut << tempBuffer.op << " " << tempBuffer.addr << " " << tempBuffer.size << " " << tempBuffer.data << endl;
		qBuffer.pop();
	}
	fBufferOut.close();
}