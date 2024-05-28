#include "Buffer.h"
#include "StorageException.h"

void Buffer::read(int lba)
{
	fillBuffer();
	storeReadData(_read(lba));
}

void Buffer::write(int lba, std::string data)
{
	checkBufferFull();

	fillBuffer();
	queueBuffer('W', lba, 0, data);
	storeBuffer();
}

void Buffer::erase(int lba, int size)
{
	checkBufferFull();

	fillBuffer();
	queueBuffer('E', lba, size, "0x00000000");
	storeBuffer();
}

queue<_Buffer> Buffer::flush() {
	fillBuffer();
	queue <_Buffer> retBuffer = qBuffer;
	clearBuffer();
	storeBuffer();

	return retBuffer;
}

int Buffer::getBufferSize() {
	fillBuffer();
	int ret =  (int)qBuffer.size();
	clearBuffer();
	return ret;
}

void Buffer::checkBufferFull()
{
	if (getBufferSize() >= MAX_BUFFER_SIZE)
		throw StorageException("Buffer full");
}

void Buffer::fillBuffer() {
	_Buffer tempBuffer;

	clearBuffer();

	fBufferIn.open(filenameBuffer);
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
	fBufferOut.open(filenameBuffer, ios::out | ios::trunc);
	while (!qBuffer.empty()) {
		tempBuffer = qBuffer.front();
		fBufferOut << tempBuffer.op << " " << tempBuffer.addr << " " << tempBuffer.size << " " << tempBuffer.data << endl;
		qBuffer.pop();
	}
	fBufferOut.close();
}

void Buffer::storeReadData(const string data) {
	fResultOut.open(filenameResult);
	fResultOut << data;
	fResultOut.close();
}

string Buffer::_read(int lba)
{
	string readData = "0000000000";

	BufferCached = false;
	_Buffer tempBuffer;
	while (!qBuffer.empty()) {
		tempBuffer = qBuffer.front();
		if (tempBuffer.op == 'W' && tempBuffer.addr == lba) {
			readData = tempBuffer.data;
			BufferCached = true;
		}
		else if (tempBuffer.op == 'E') {
			int low = tempBuffer.addr;
			int high = tempBuffer.addr + tempBuffer.size;

			if (low <= lba && lba < high) {
				readData = "0x00000000";
				BufferCached = true;
			}
		}
		qBuffer.pop();
	}

	return readData;
}

bool Buffer::BufferHit() {
	return BufferCached;
}