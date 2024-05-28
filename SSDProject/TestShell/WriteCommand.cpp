#include "Command.h"
#include <stdexcept>
#include "InputValidChecker.cpp"

using namespace std;

class WriteCommand : public Command {
public:
	WriteCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {
		if (receiver == nullptr) {
			throw invalid_argument("Need valid write receiver");
		}

		if (!checker.check(v, InputValidChecker::TYPE_CMD_LBA_VAL)) {
			throw invalid_argument("Need valid argument");
		}

		string wrCmd;
		string space = " ";

		wrCmd.append(cmd);
		wrCmd.append(space);
		wrCmd.append(v[1]);
		wrCmd.append(space);
		wrCmd.append(v[2]);

		int ret = invoke(wrCmd);
		receiver->write(ret);
	}
private:
	const string cmd = "W";
};
