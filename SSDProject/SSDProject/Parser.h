#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class StorageDriver;
class Command;

class Parser {
public:
	Parser(StorageDriver* driver) : m_driver{ driver } {}
	std::pair<Command*, std::vector<std::string>> parse(int argc, char** argv);
private:
	StorageDriver* m_driver;
};

void checkCmdValidity(int argc, const std::string& argv0, const std::string& argv1);
