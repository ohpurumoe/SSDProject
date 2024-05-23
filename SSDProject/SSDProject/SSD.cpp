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
	ofstream fNandOut, fResultOut;
	ifstream fNandIn;
	map<int, string> mapNand;

	void writeMapToFile() {
		fNandOut.open(nandname);
		for (auto iter = mapNand.begin(); iter != mapNand.end(); ++iter) {
			fNandOut << iter->first << " " << iter->second << endl;
		}
		fNandOut.close();
	}

	void writeDataToMap(const int LBA, const string data) {
		if (!mapNand.empty() && LBA == mapNand.find(LBA)->first) {
			mapNand.find(LBA)->second = data;
		}
		else {
			mapNand.insert({ LBA, data });
		}
	}
	void fillMap() {
		string line, readData;

		mapNand.clear();
		fNandIn.open(nandname);
		while (getline(fNandIn, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = line.substr(line.find(' '), 11).substr(1, 10);
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