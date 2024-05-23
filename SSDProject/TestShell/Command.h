#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Receiver {
public:
    // TODO : need to check whether print log or not.
    void write(int retCode) { 
        returnCode = retCode;
        std::cout << "Executing write command : " << retCode << std::endl;
    }

    void read(int retCode) {
        returnCode = retCode;
        std::cout << "Executing read command : " << retCode << std::endl;
    }
        
    void exit() const { std::cout << "Executing exit command" << std::endl; }
    void help() const { std::cout << "Executing help command" << std::endl; }
    void fullwrite() const { std::cout << "Executing fullwrite command" << std::endl; }
    void fullread() const { std::cout << "Executing fullread command" << std::endl; }

    void mock() const { std::cout << "Executing mock command" << std::endl; }

    int getResultCode() const { return returnCode; }

private:
    int returnCode;
};

class Command {
public:
    Command(Receiver* receiver = nullptr) : receiver(receiver) {}
    virtual ~Command() {}
    virtual void execute(std::vector<std::string> v) const = 0;
    int invoke(std::string cmd) const {
        std::string arg = ssdExe + " " + cmd;
        return system(arg.c_str());
    }

private:
    const std::string ssdExe = "..\\x64\\Debug\\SSD.exe";
protected:
    Receiver* receiver;
};

