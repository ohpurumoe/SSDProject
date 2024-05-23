#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <exception>
#include "IStorage.h"

using namespace std;
class SSD : public IStorage {
public:
	SSD(string nandname = "nand.txt", string resultname = "result.txt")
		: nandname{ nandname },
		resultname{ resultname } {}

	int read(int LBA) override {
		storeReadData(readData(LBA));

		return 0;
	}

	void write(int LBA, string data) override {
		fillMap();
		writeDataToMap(LBA, data);
		writeMapToFile();
	}

private:
	string nandname;
	string resultname;
	fstream fNand, fResult;
	map<int, string> mapNand;
	const char BLANK = ' ';
	const int DATA_SIZE = 10;

	void writeMapToFile() {
		fNand.open(nandname, ios::out);
		for (auto iter : mapNand) {
			fNand << iter.first << " " << iter.second << endl;
		}
		fNand.close();
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
		return removeAddr.substr(1, DATA_SIZE);
	}
	void checkFileOpen(fstream file) {
		if (file.is_open()) {
			throw std::exception("file open error");
		}
	}
	void fillMap() {
		string line, readData;

		mapNand.clear();
		fNand.open(nandname, ios::in);
		while (getline(fNand, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = getData(line);
			mapNand.insert({ addr, readData });
		}
		fNand.close();
	}
	string readData(const int LBA) {
		string line, readData;

		fNand.open(nandname, ios_base::in);
		while (getline(fNand, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = line.substr(line.find(' '), 11).substr(1, 10);
			if (addr == LBA) break;
		}
		fNand.close();

		return readData;
	}
	void storeReadData(const string data) {
		fResult.open(resultname, ios::out);
		fResult << data;
		fResult.close();
	}
};