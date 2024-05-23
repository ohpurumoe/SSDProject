#pragma once
#include <stdexcept>
#include <string>
enum class Command{
	READ,
	WRITE
};

Command parse(int argc, char** argv){
	return Command::WRITE;
}
