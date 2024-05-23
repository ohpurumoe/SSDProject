#include "Command.h"
#include <stdexcept>

using namespace std;

class WriteCommand : public Command {
public:
	WriteCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) const override {
		if (v.size() < 2) {
			throw invalid_argument("Need two argument for write command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need valid write receiver");
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
