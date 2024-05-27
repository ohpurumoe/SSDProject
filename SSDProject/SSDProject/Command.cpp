#pragma once
#include <string>
#include <vector>
#include "Command.h"
#include "StorageDriver.cpp"

void ReadCommand::execute(const std::vector<std::string>& args) {
	m_driver->read(std::stoi(args[0]));
}

void WriteCommand::execute(const std::vector<std::string>& args) {
	m_driver->write(std::stoi(args[0]), args[1]);
}
