﻿#include "Command.h"
#include <stdexcept>

using namespace std;

class FullReadCommand : public Command {
public:
	FullReadCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {
		if (v.size() != 1) {
			throw invalid_argument("Need No argument for full read command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need Receiver for read command");
		}

		for (int lba = 0; lba < 100; lba++) {

			string rdCmd;
			string space = " ";

			rdCmd.append(cmd);
			rdCmd.append(space);
			rdCmd.append(to_string(lba));

			int ret = invoke(rdCmd);

			// read result
			if (ret == 0) {
				string result = getReadResult();
				cout << result << endl;
			}
			receiver->read(ret);
		}
	}

private:
	const string cmd = "R";
	const std::string ssdResult = ".\\result.txt";

	string getReadResult() const {
		ifstream ifs;

		ifs.open(ssdResult);
		string result = string((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
		ifs.close();

		return result;
	}
};
