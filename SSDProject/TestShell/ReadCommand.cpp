#include "Command.h"
#include <stdexcept>

using namespace std;

class ReadCommand : public Command {
public:
	ReadCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) const override {
		if (v.size() < 2) {
			throw invalid_argument("Need two argument for read command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need valid read receiver");
		}

		string rdCmd;
		string space = " ";

		rdCmd.append(cmd);
		rdCmd.append(space);
		rdCmd.append(v[1]);

		int ret = invoke(rdCmd);
		receiver->read(ret);
	}
private:
	const string cmd = "R";
};
