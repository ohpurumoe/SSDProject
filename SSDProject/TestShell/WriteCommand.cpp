#include "Command.h"
#include <stdexcept>

using namespace std;

class WriteCommand : public Command {
public:
	WriteCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) const override {
		if (v.size() < 2) {
			throw invalid_argument("Need two argument for read command");
		}
	}
private:
	const string cmd = "W";
};
