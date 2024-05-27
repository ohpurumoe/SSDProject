#include "Parser.h"
#include "Command.h"

std::pair<Command*, std::vector<std::string>> 
Parser::parse(int argc, char** argv) {
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
		return { new WriteCommand(m_driver), args};
	}
	return { new EraseCommand(m_driver), args};
}

void checkCmdValidity(int argc, const std::string& argv0, const std::string& argv1) {
	if (argv1 != "R" && argv1 != "W" && argv1 != "E") {
		throw std::runtime_error("First argument must be \"R\" or \"W\". Please check usage of ssd.");
	}
	if (argv1 == "R" && argc != 3) {
		throw std::runtime_error("Wrong usage of ssd Read. Please check usage of ssd.");
	}
	if (argv1 == "W" && argc != 4) {
		throw std::runtime_error("Wrong usage of ssd Write. Please check usage of ssd.");
	}
	if (argv1 == "E" && argc != 4) {
		throw std::runtime_error("Wrong usage of ssd Erase. Please check usage of ssd.");
	}
}

