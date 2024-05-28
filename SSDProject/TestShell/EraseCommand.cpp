#include "Command.h"
#include <stdexcept>
#include <fstream>

using namespace std;

class EraseCommand : public Command {
public:
	EraseCommand(IReceiver* receiver) : Command(receiver) {}
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

		return makeCommand(v[1], v[2]);
	}

	string getEraseRangeCommand(vector<std::string> v) {
		if (!checker.check(v, InputValidChecker::TYPE_CMD_LBA_LBA)) {
			throw invalid_argument("Need valid argument");
		}

		int start_lba = stoi(v[1]);
		int end_lba = stoi(v[2]);

		if (start_lba >= end_lba)	{
			throw invalid_argument("Need valid argument");
		}

		int size = end_lba - start_lba;
		if (size > 10) {
			throw invalid_argument("Need valid argument");
		}

		return makeCommand(v[1], to_string(size));
	}

	string makeCommand(string lba, string size) {
		string eraseCmd;
		string space = " ";

		eraseCmd.append(cmd);
		eraseCmd.append(space);
		eraseCmd.append(lba);
		eraseCmd.append(space);
		eraseCmd.append(size);

		return eraseCmd;
	}

	const string cmd = "E";
};
