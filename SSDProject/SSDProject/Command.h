#pragma once
#include "StorageDriver.cpp"
#include <stdexcept>
#include <vector>

class Command {
public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};

class StorageDriver;

class ReadCommand : public Command {
public:
	ReadCommand(StorageDriver* driver) : m_driver{ driver } {}
	void execute(const std::vector<std::string>& args) override {
		m_driver->read(std::stoi(args[0]));
	}
	StorageDriver* m_driver;
};

class WriteCommand : public Command {
public:
	WriteCommand(StorageDriver* driver) : m_driver{ driver } {}
	void execute(const std::vector<std::string>& args) override {
		m_driver->write(std::stoi(args[0]), args[1]);
	}
	StorageDriver* m_driver;
};

class EraseCommand : public Command {
public:
	EraseCommand(StorageDriver* driver) : m_driver{ driver } {}
	void execute(const std::vector<std::string>& args) override {
		m_driver->erase(std::stoi(args[0]), std::stoi(args[1]));
	}
	StorageDriver* m_driver;
};

class FlushCommand : public Command {
public:
	FlushCommand(StorageDriver* driver) : m_driver{ driver } {}
	void execute(const std::vector<std::string>& args) override {
		m_driver->flush();
	}
	StorageDriver* m_driver;
};
