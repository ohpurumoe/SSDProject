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

void EraseCommand::execute(const std::vector<std::string>& args) {
	m_driver->erase(std::stoi(args[0]), std::stoi(args[1]));
}

void FlushCommand::execute(const std::vector<std::string>& args) {
	m_driver->flush();
}
