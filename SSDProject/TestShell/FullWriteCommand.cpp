#include "Command.h"
#include <stdexcept>

using namespace std;

class FullWriteCommand : public Command {
public:
	FullWriteCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) const override {
		if (v.size() < 2) {
			throw invalid_argument("Need two argument for full write command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need Receiver for full write command");
		}

		for (int lba = 0; lba < 100; lba++) {
			string wrCmd = "";
			string space = " ";

			wrCmd.append(cmd);
			wrCmd.append(space);
			wrCmd.append(to_string(lba));
			wrCmd.append(space);
			wrCmd.append(v[1]);

			int ret = invoke(wrCmd);
			receiver->write();
		}
	}
private:
	const string cmd = "W";
};
