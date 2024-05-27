#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "InputValidChecker.cpp"

using namespace std;

class Receiver {
public:
    void write(int retCode) { 
        returnCode = retCode;
    }

    void read(int retCode) {
        returnCode = retCode;
    }
        
    void exit() const { }
    void help() const { }
    void fullwrite() const { }
    void fullread() const { }

    void mock() const { }

    int getResultCode() const { return returnCode; }

private:
    int returnCode;
};

class Command {
public:
    Command(Receiver* receiver = nullptr) : receiver(receiver) {}
    virtual ~Command() {}
    virtual void execute(std::vector<std::string> v) = 0;
    int invoke(std::string cmd) const {
        std::string arg = ssdExe + " " + cmd;
        return system(arg.c_str());
    }

private:
    const std::string ssdExe = "..\\x64\\Debug\\SSD.exe";
protected:
    Receiver* receiver;
    InputValidChecker checker;
};

