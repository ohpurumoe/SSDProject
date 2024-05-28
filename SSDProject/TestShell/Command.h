#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "InputValidChecker.cpp"

using namespace std;

class IReceiver {
public:
    virtual void write(int retCode) = 0;
    virtual void read(int retCode) = 0;
    virtual void erase(int retCode) = 0;

    virtual void fullwrite() = 0;
    virtual void fullread() = 0;

    virtual void setResultCode(int retCode) = 0;
    virtual int getResultCode() = 0;

protected:
    int returnCode;
};

class Receiver : public IReceiver {
public:
    void write(int retCode) override {
        returnCode = retCode;
    }

    void read(int retCode) override {
        returnCode = retCode;
    }

    void erase(int retCode) override {
        returnCode = retCode;
    }

    void exit() const { }
    void help() const { }
    void fullwrite() override { }
    void fullread() override { }

    void setResultCode(int retCode) override {
        returnCode = retCode;
    }
    int getResultCode() override { return returnCode; }
};

class Command {
public:
    Command(IReceiver* receiver = nullptr) : receiver(receiver) {}
    virtual ~Command() {}
    virtual void execute(std::vector<std::string> v) = 0;
    int invoke(std::string cmd) const {
        std::string arg = ssdExe + " " + cmd;
        return system(arg.c_str());
    }

private:
    const std::string ssdExe = "..\\x64\\Debug\\SSD.exe";
protected:
    IReceiver* receiver;
    InputValidChecker checker;
};

