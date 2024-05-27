#pragma once

#define MAKESINGLE(classname)									\
public:															\
	static classname& getInstance() {							\
		static classname instance{};							\
		return instance;										\
	}															\
																\
private:														\
	classname() { }												\
	classname& operator=(const classname& other) = delete;		\
	classname(const classname& other) = delete;					\

#define print(msg) printLog(__FUNCTION__, msg)

#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>

using namespace std;

enum LoggerLevel {
	LOGGER_LEVEL_OFF,
	LOGGER_LEVEL_DEBUGGING,
};

class Logger {
	MAKESINGLE(Logger)
public:
	void setLoggerLevel(LoggerLevel level);
	void printLog(string funcName, string messages);

	int getFileSize(const string& filename);
	string getDateFromtString();
	void saveUntilLog();
	void modifyLogToZip();
	void checkLogFileSize(size_t logSize);
	bool openLogFile(fstream& logFstream, const std::string& filename);
	void closeLogFile();
	void saveLog(string log);
	void formatLog(string& logString, string funcName, string message);

private:
	static constexpr char LOG_FILE_NAME_LATEST[11] = "latest.log";
	static constexpr int MAX_LOG_SIZE = 1024 * 10; // 10KB
	
	LoggerLevel logLevel = LOGGER_LEVEL_DEBUGGING;
	fstream logFstream;
	streampos logFileSize;
};