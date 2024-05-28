#pragma once
#include <string>
#include <queue>
#include <fstream>
#include "IStorage.h"

using namespace std;

class Buffer :
	public IStorage
{
public:
	Buffer(string buffer = "buffer.txt", string result = "result.txt")
		: filenameBuffer{ buffer }, filenameResult{ result } {}

	}


	// IStorage을(를) 통해 상속됨
	void read(int lba) override;
	void write(int lba, string data) override;
	void erase(int lba, int size) override;
	int getBufferSize();
	queue<_Buffer> flush();

private:
	string filenameBuffer, filenameResult;
	string resultname;

	ifstream fBufferIn;
	ofstream fBufferOut, fResultOut;

	queue <_Buffer> qBuffer;
	const int BUFFER_SIZE = 10;

	void queueBuffer(char, int, int, string);
	void fillBuffer();
	void clearBuffer();
	void storeBuffer();
	void storeReadData(const string data);
};

