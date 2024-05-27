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

		int ret = invoke(eraseCmd);
		receiver->erase(ret);
	}
private:
	const string cmd = "E";
};
