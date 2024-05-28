#include "Command.h"
#include <stdexcept>
#include "ReadCommand.cpp"

using namespace std;

class FullReadCommand : public Command {
private:
	const int argc = 2;
public:
	FullReadCommand(IReceiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {
		if (v.size() != 1) {
			throw invalid_argument("Need No argument for full read command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need Receiver for read command");
		}

		ReadCommand readCommand(receiver);
		if (v.size() < argc) {
			v.resize(argc);
		}

		for (int lba = 0; lba < 100; lba++) {
			v[1] = to_string(lba);
			readCommand.execute(v);
		}
	}
};
