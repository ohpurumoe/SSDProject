#include "Command.h"
#include <stdexcept>

using namespace std;

class ReadCommand : public Command {
public:
	ReadCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) const override {
		// TODO: need to implement
	}
private:
	const string cmd = "R";
};
