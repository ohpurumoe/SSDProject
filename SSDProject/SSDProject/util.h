#pragma once
#include <stdexcept>
#include <string>
enum class Command{
	READ,
	WRITE
};

Command parse(int argc, char** argv){
	if(argc<2){
		throw std::runtime_error("ssd cmd argument number is lesser than 1. Please check usage of ssd.");
	}
	std::string argv0 = argv[0];
	if(argv0 != "ssd"){
		throw std::runtime_error("Wrong cmd used.");
	}
	std::string argv1 = argv[1];
	if(argv1 != "R" && argv1 != "W"){
		throw std::runtime_error("First argument must be \"R\" or \"W\". Please check usage of ssd.");
	}
	if(argv1 == "R" && argc != 3){
		throw std::runtime_error("Wrong usage of ssd Read. Please check usage of ssd.");
	}
	if(argv1 == "W" && argc != 4){
		throw std::runtime_error("Wrong usage of ssd Write. Please check usage of ssd.");
	}

	if(argv1 == "R"){
		return Command::READ;
	}
	return Command::WRITE;
}
