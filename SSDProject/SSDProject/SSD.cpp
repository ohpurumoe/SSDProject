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
		string line, readData;
		fNandIn.open(nandname, ios_base::in);
		while (getline(fNandIn, line)) {
			if (line.size() == 0) continue;
			int addr = stoi(line);
			readData = line.substr(line.find(' '), 11).substr(1, 10);
			if (addr == LBA) break;
		}
		fNandIn.close();

		fResultOut.open(resultname);
		fResultOut << readData;
		fResultOut.close();

		return 0;
	}
	void write(int LBA, string data) override {
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

		if (!mapNand.empty() && LBA == mapNand.find(LBA)->first) {
			mapNand.find(LBA)->second = data;
		}
		else {
			mapNand.insert({ LBA, data });
		}

		fNandOut.open(nandname);
		for (auto iter = mapNand.begin(); iter != mapNand.end(); ++iter) {
			fNandOut << iter->first << " " << iter->second << endl;
		}
		fNandOut.close();
	}
private:
	string nandname;
	string resultname;
	ofstream fNandOut, fResultOut;
	ifstream fNandIn;
	map<int, string> mapNand;
};