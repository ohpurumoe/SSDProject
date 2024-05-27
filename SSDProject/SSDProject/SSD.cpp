#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <regex>
#include "IStorage.h"
#include "StorageException.h"

using namespace std;
class SSD : public IStorage {
public:
	SSD(string nandname = "nand.txt", string resultname = "result.txt")
		: nandname{ nandname },
		resultname{ resultname } {}

	string read(int LBA) override {
		if (LBA < ADDR_LOW || LBA > ADDR_HIGH) {
			throw StorageException("LBA는 0 ~ 99 사이의 값이어야 합니다. LBA : " + to_string(LBA));
		}

		auto data = readData(LBA);
		storeReadData(data);

		return data;
	}

	void write(int LBA, string data) override {
		if (LBA < ADDR_LOW || LBA > ADDR_HIGH) {
			throw StorageException("LBA는 0 ~ 99 사이의 값이어야 합니다. LBA : " + to_string(LBA));
		}

		regex re("^0x[A-F0-9]{8}");
		if (!regex_match(data, re)) {
			throw StorageException("data는 0x로 시작하고 숫자와 대문자 8개로 이루어져야합니다. data : " + data);
		}

		fillMapFromFile();
		writeDataToMap(LBA, data);
		writeMapToFile();
	}

	void erase(int LBA, int size) override {
		if (LBA < ADDR_LOW || LBA > ADDR_HIGH) {
			throw StorageException("LBA는 0 ~ 99 사이의 값이어야 합니다. LBA : " + to_string(LBA));
		}

		fillMapFromFile();

		for (int i = LBA; i < LBA + size; i++) {
			writeDataToMap(i, "0x00000000");
		}

		writeMapToFile();
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
	string getData(string data) {
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