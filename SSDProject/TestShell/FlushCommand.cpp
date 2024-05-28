#pragma once

#include "Command.h"
#include <stdexcept>

using namespace std;

class FlushCommand : public Command {
public:
	FlushCommand(IReceiver* receiver) : Command(receiver) {}
	void execute(vector<string> v) override {
		if (receiver == nullptr) {
			throw invalid_argument("Need valid read receiver");
		}

		if (!checker.check(v, InputValidChecker::TYPE_CMD)) {
			throw invalid_argument("Need valid argument");
		}

		string flushCmd;
		string space = " ";

		flushCmd.append(cmd);

		int ret = invoke(flushCmd);
		receiver->flush(ret);
	}
private:
	const string cmd = "F";
};
