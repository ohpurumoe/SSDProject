#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;
class SSD /* : public iStorage */ {
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
	int read(int LBA) {
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
	int write(int LBA, string data) {
		if (!fNandOut) return -1;

		fNandOut << LBA << " " << data << endl;
	}
private:
	string nandname;
	string resultname;
	ofstream fNandOut, fResultOut;
	ifstream fNandIn;
	map<int, string> data;
};