#include "Command.h"
#include <stdexcept>
#include "WriteCommand.cpp"

using namespace std;

class FullWriteCommand : public Command {
private:
	const int argc = 3;
public:
	FullWriteCommand(IReceiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {
		if (v.size() < 2) {
			throw invalid_argument("Need two argument for full write command");
		}

		if (receiver == nullptr) {
			throw invalid_argument("Need Receiver for full write command");
		}

		WriteCommand writeCommand(receiver);
		if (v.size() < argc) {
			v.resize(argc);
		}
		string value = v[1];
		for (int lba = 0; lba < 100; lba++) {
			v[1] = to_string(lba);
			v[2] = value;
			writeCommand.execute(v);
		}
	}
};
