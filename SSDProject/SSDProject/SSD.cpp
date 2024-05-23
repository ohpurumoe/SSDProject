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

	string read(int LBA) override {
		auto data = readData(LBA);
		storeReadData(data);

		return data;
	}

	void write(int LBA, string data) override {
		fillMap();

		writeDataToMap(LBA, data);

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
		return removeAddr.substr(1, DATA_SIZE);
	}
	void fillMap() {
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
		string line, readData;

		fNandIn.open(nandname, ios_base::in);
		while (getline(fNandIn, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = line.substr(line.find(' '), 11).substr(1, 10);
			if (addr == LBA) break;
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