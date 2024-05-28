#pragma once

#include "Command.h"
#include <stdexcept>

using namespace std;

class FlushCommand : public Command {
public:
	FlushCommand(IReceiver* receiver) : Command(receiver) {}
	void execute(vector<string> v) override {

	}
private:
	const string cmd = "F";
};
