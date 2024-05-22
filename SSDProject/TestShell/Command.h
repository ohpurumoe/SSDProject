#include <iostream>
#include <string>
#include <map>
#include <memory>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};

class Receiver {
public:
    // TODO : change to 'real storageDriver'
    void write() const { std::cout << "Executing write command" << std::endl; }
    void read() const { std::cout << "Executing read command" << std::endl; }
    void exit() const { std::cout << "Executing exit command" << std::endl; }
    void help() const { std::cout << "Executing help command" << std::endl; }
    void fullwrite() const { std::cout << "Executing fullwrite command" << std::endl; }
    void fullread() const { std::cout << "Executing fullread command" << std::endl; }
};

class Invoker {
public:
    void setCommand(const std::string& name, std::shared_ptr<Command> command) {
        commands_[name] = command;
    }

    void executeCommand(const std::string& name) const {
        auto it = commands_.find(name);
        if (it != commands_.end()) {
            it->second->execute();
        }
        else {
            std::cout << "Command not found" << std::endl;
        }
    }

private:
    std::map<std::string, std::shared_ptr<Command>> commands_;
};

#if 1 // TODO : will remove. Below is example 
class WriteCommand : public Command {
public:
    WriteCommand(Receiver* receiver) : receiver_(receiver) {}
    void execute() const override { receiver_->write(); }
private:
    Receiver* receiver_;
};

class ReadCommand : public Command {
public:
    ReadCommand(Receiver* receiver) : receiver_(receiver) {}
    void execute() const override { receiver_->read(); }
private:
    Receiver* receiver_;
};

int example_main() {
    Receiver receiver;
    Invoker invoker;

    invoker.setCommand("write", std::make_shared<WriteCommand>(&receiver));
    invoker.setCommand("read", std::make_shared<ReadCommand>(&receiver));
#if 0
    invoker.setCommand("exit", std::make_shared<ExitCommand>(&receiver));
    invoker.setCommand("help", std::make_shared<HelpCommand>(&receiver));
    invoker.setCommand("fullwrite", std::make_shared<FullWriteCommand>(&receiver));
    invoker.setCommand("fullread", std::make_shared<FullReadCommand>(&receiver));
#endif

    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "exit") {
            invoker.executeCommand(command);
            break;
        }

        invoker.executeCommand(command);
    }

    return 0;
}
#endif