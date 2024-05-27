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
	Buffer(string filename = "buffer.txt")
		: filename{ filename } {}

    // IStorage을(를) 통해 상속됨
    string read(int lba) override;
    void write(int lba, string data) override;
    void erase(int lba, int size) override;
	int getBufferSize();
    queue<_Buffer>& flush();

private:
	string filename;
	ifstream fBufferIn;
	ofstream fBufferOut;

	queue <_Buffer> qBuffer;
	const int BUFFER_SIZE = 10;

	void queueBuffer(char, int, int, string);
	void fillBuffer();
	void storeBuffer();
};

