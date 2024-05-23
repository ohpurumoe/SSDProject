#pragma once
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "StorageDriver.cpp"

enum class Command{
	READ,
	WRITE
};

using CommandArgsPair = std::pair<Command, std::vector<std::string>>;

void checkCmdValidity(int argc, const std::string& argv0, const std::string& argv1) {
	if (argc < 2) {
		throw std::runtime_error("ssd cmd argument number is lesser than 1. Please check usage of ssd.");
	}
	if (argv0 != "ssd") {
		throw std::runtime_error("Wrong cmd used.");
	}
	if (argv1 != "R" && argv1 != "W") {
		throw std::runtime_error("First argument must be \"R\" or \"W\". Please check usage of ssd.");
	}
	if (argv1 == "R" && argc != 3) {
		throw std::runtime_error("Wrong usage of ssd Read. Please check usage of ssd.");
	}
	if (argv1 == "W" && argc != 4) {
		throw std::runtime_error("Wrong usage of ssd Write. Please check usage of ssd.");
	}
}

CommandArgsPair parse(int argc, char** argv){
	std::string argv0 = argv[0];
	std::string argv1 = argv[1];
	try {
		checkCmdValidity(argc, argv0, argv1);
	}
	catch (...) {
		throw;
	}
	std::vector<std::string> args;
	for (int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}
	if(argv1 == "R"){
		return { Command::READ, args };
	}
	return { Command::WRITE, args };
}

void execute(StorageDriver& driver, const CommandArgsPair& cmd_arg)
{

}
