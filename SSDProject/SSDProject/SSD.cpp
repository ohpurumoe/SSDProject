#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "IStorage.h"

using namespace std;
class SSD : public IStorage {
public:
	SSD(string nandname = "nand.txt", string resultname = "result.txt")
		: nandname{ nandname },
		resultname{ resultname } {}
	void open() {
		fNandOut.open(nandname);
		fNandIn.open(nandname);
		fResultOut.open(resultname);
	}
	void close() {
		fNandOut.close();
		fNandIn.close();
		fResultOut.close();
	}
	int read(int LBA) override {
		if (!fNandIn) return 0;

		string readData;
		string line;
		while (getline(fNandIn, line)) {
			int addr = stoi(line);
			readData = line.substr(line.find(' '), 10);
			readData = readData.substr(1, 10);
		}
		fResultOut << readData;

		return 0;
	}
	void write(int LBA, string data) override {
		if (!fNandOut) return;

		fNandOut << LBA << " " << data << endl;
	}
private:
	string nandname;
	string resultname;
	ofstream fNandOut, fResultOut;
	ifstream fNandIn;
};