#include "Command.h"
#include <stdexcept>
#include <fstream>

using namespace std;

class EraseCommand : public Command {
public:
	EraseCommand(Receiver* receiver) : Command(receiver) {}
	void execute(std::vector<std::string> v) override {

	}
private:
	const string cmd = "E";
};
