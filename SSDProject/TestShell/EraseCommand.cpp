#include "Command.h"
#include <stdexcept>
#include <fstream>

using namespace std;

class EraseCommand : public Command {
public:
	EraseCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {
		if (receiver == nullptr) {
			throw invalid_argument("Need valid read receiver");
		}

		string eraseCmd;

		try {
			if (v[0] == "erase_range") {
				eraseCmd = getEraseRangeCommand(v);
			}
			else {
				eraseCmd = getEraseCommand(v);
			}
		}
		catch (...) {
			throw invalid_argument("Need valid argument");
		}

		int ret = invoke(eraseCmd);
		receiver->erase(ret);
	}
private:

	string getEraseCommand(vector<std::string> v) {

		if (!checker.check(v, InputValidChecker::TYPE_CMD_LBA_SIZE)) {
			throw invalid_argument("Need valid argument");
		}

		string eraseCmd;
		string space = " ";

		eraseCmd.append(cmd);
		eraseCmd.append(space);
		eraseCmd.append(v[1]);
		eraseCmd.append(space);
		eraseCmd.append(v[2]);

		return eraseCmd;
	}

	string getEraseRangeCommand(vector<std::string> v) {
		if (!checker.check(v, InputValidChecker::TYPE_CMD_LBA_LBA)) {
			throw invalid_argument("Need valid argument");
		}

		string eraseCmd;
		string space = " ";

		int start_lba = stoi(v[1]);
		int end_lba = stoi(v[2]);

		if (start_lba >= end_lba)	{
			throw invalid_argument("Need valid argument");
		}

		int size = end_lba - start_lba;
		if (size > 10) {
			throw invalid_argument("Need valid argument");
		}

		eraseCmd.append(cmd);
		eraseCmd.append(space);
		eraseCmd.append(v[1]);
		eraseCmd.append(space);
		eraseCmd.append(to_string(size));

		return eraseCmd;
	}

	const string cmd = "E";
};
