#include "Command.h"


class WriteCommand : public Command {
public:
    WriteCommand(Receiver* receiver) : Command(receiver) {}
    void execute(std::vector<std::string> v) const override {
        // TODO: need to implement
    }
private:
    const string cmd = "W";
};
