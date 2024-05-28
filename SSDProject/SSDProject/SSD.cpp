#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <regex>
#include <queue>
#include "IStorage.h"
#include "StorageException.h"

using namespace std;
class SSD : public IStorage {
public:
	SSD(string nandname = "nand.txt", string resultname = "result.txt")
		: nandname{ nandname },
		resultname{ resultname } {}

	void read(int LBA) override {
		_read(LBA);
	}

	void write(int LBA, string data) override {
		_write(LBA, data);
	}

	void erase(int LBA, int size) override {
		_erase(LBA, size);
	}

private:
	string nandname;
	string resultname;
	ofstream fNandOut, fResultOut;
	ifstream fNandIn;
	map<int, string> mapNand;

	const char BLANK = ' ';
	const int DATA_SIZE = 10;
	const string EMPTY = "0x00000000";
	const int ADDR_HIGH = 99;
	const int ADDR_LOW = 0;


	void _read(int LBA) {
		storeReadData(readData(LBA));
	}

	void _write(int LBA, string data) {
		fillMapFromFile();
		writeDataToMap(LBA, data);
		writeMapToFile();
	}

	void _erase(int LBA, int size) {
		fillMapFromFile();
		for (int addr = LBA; addr < LBA + size; addr++) {
			writeDataToMap(addr, EMPTY);
		}
		writeMapToFile();
	}

	void writeMapToFile() {
		fNandOut.open(nandname);
		for (auto iter : mapNand) {
			fNandOut << iter.first << " " << iter.second << endl;
		}
		fNandOut.close();
	}

	void writeDataToMap(const int LBA, const string data) {
		if (!mapNand.empty() && mapNand.find(LBA) != mapNand.end() && LBA == mapNand.find(LBA)->first) {
			mapNand.find(LBA)->second = data;
		}
		else {
			mapNand.insert({ LBA, data });
		}
	}

	string getData(const string data) {
		string removeAddr = data.substr(data.find(BLANK), DATA_SIZE + sizeof(BLANK));
		return removeAddr.substr(sizeof(BLANK), DATA_SIZE);
	}

	void fillMapFromFile() {
		string line, readData;

		mapNand.clear();
		fNandIn.open(nandname);
		while (getline(fNandIn, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = getData(line);
			mapNand.insert({ addr, readData });
		}
		fNandIn.close();
	}

	string readData(const int LBA) {
		string line, readData = EMPTY;

		fNandIn.open(nandname, ios_base::in);
		while (getline(fNandIn, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = getData(line);
			if (addr == LBA) break;
			readData = EMPTY;
		}
		fNandIn.close();

		return readData;
	}

	void storeReadData(const string data) {
		fResultOut.open(resultname);
		fResultOut << data;
		fResultOut.close();
	}
};