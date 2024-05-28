#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "Command.h"

void checkCmdValidity(int argc, const std::string& argv0, const std::string& argv1);

class Parser {
public:
	Parser(StorageDriver* driver) : m_driver{ driver } {}
	std::pair<Command*, std::vector<std::string>> parse(int argc, char** argv) {
		if (argc < 2) {
			throw std::runtime_error("ssd cmd argument number is lesser than 1. Please check usage of ssd.");
		}
		std::string argv0 = argv[0];
		std::string argv1 = argv[1];
		try {
			checkCmdValidity(argc, argv0, argv1);
		}
		catch (...) {
			throw;
		}
		std::vector<std::string> args;
		for (int i = 2; i < argc; ++i) {
			args.push_back(argv[i]);
		}
		if (argv1 == "R") {
			return { new ReadCommand(m_driver), args };
		}
		if (argv1 == "W") {
			return { new WriteCommand(m_driver), args };
		}
		if (argv1 == "E") {
			return { new EraseCommand(m_driver), args };
		}
		return { new FlushCommand(m_driver), args };
	}
private:
	StorageDriver* m_driver;
};

void checkCmdValidity(int argc, const std::string& argv0, const std::string& argv1) {
	if (argv1 != "R" && argv1 != "W" && argv1 != "E" && argv1 != "F") {
		throw std::runtime_error("First argument must be \"R\" or \"W\" or \"E\" or \"F\".");
	}
	if (argv1 == "R" && argc != 3) {
		throw std::runtime_error("Wrong usage for ssd Read. Please write 1 arguments: addr");
	}
	if (argv1 == "W" && argc != 4) {
		throw std::runtime_error("Wrong usage for ssd Write. Please write 2 arguments: addr, data");
	}
	if (argv1 == "E" && argc != 4) {
		throw std::runtime_error("Wrong usage for ssd Erase. Please write 2 arguments: addr, size");
	}
	if (argv1 == "F" && argc != 2) {
		throw std::runtime_error("Wrong usage for ssd Flush. Please do not write any arguments.");
	}
}
