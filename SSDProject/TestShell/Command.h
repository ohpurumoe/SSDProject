#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Command {
public:
	virtual ~Command() {}
	virtual void execute(std::vector<std::string> v) const = 0;

	int invoke(string cmd) {
		string arg = ssdExe + " " + cmd;
		return system(arg.c_str());
	}
private:
	const string ssdExe = "..\\x64\\Debug\\SSD.exe";
};

class Receiver {
public:
	// TODO : need to check whether print log or not.
	void write() const { std::cout << "Executing write command" << std::endl; }
	void read() const { std::cout << "Executing read command" << std::endl; }
	void exit() const { std::cout << "Executing exit command" << std::endl; }
	void help() const { std::cout << "Executing help command" << std::endl; }
	void fullwrite() const { std::cout << "Executing fullwrite command" << std::endl; }
	void fullread() const { std::cout << "Executing fullread command" << std::endl; }
};