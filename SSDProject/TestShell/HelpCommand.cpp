#include "Command.h"
#include "unordered_map"

class HelpCommand : public Command {
public:
    HelpCommand(Receiver* receiver) : receiver_(receiver) {
        helpMaps = {
            {"write", "write : Save data into the LBA ex) wrtie 3 0xAAAABBBB "},
            {"read", "read : Load data from the LBA ex) read 3"},
            {"exit", "exit : Exit this shell"},
            {"help", "help : Display this help message.ex) help write"},
            {"fullwrite", "full write : Perform save data to LBA's all range (0~99) ex) fullwrite 0xABCDFFFF"},
            {"fullread", "full read : Perform load data from LBA's all range (0~99) ex) full read"},
            {"testapp1", "testapp1 : Execute test application 1."},
            {"testapp2", "testapp2 : Execute test application 2."}
        };
    }

    void execute(std::vector<std::string> v) const override {
        if (receiver_ == nullptr) {
            throw invalid_argument("receiver_ is nullptrr");;
        }

        receiver_->help();

        if (v.size() > 2) {
            throw invalid_argument("Max argument is two for help command");
        }

        if (v.size() == 1) {
            for (const auto& cmd : helpMaps)
                cout << cmd.second << endl;
        }
        else {
            string command = *(v.begin()+1);
            auto it = helpMaps.find(command);
            if (it != helpMaps.end())
                cout << it->second << endl;
            else
                throw invalid_argument("Not Help available for command");

        }
        return;
    }
private:
    Receiver* receiver_;
    unordered_map<string, string> helpMaps;
};
