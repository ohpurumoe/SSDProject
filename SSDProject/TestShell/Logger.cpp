#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <vector>
#include <windows.h>

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

#define GET_MACRO(_1,_2,NAME,...) NAME
#define print(...) GET_MACRO(__VA_ARGS__, print2, print1)(__VA_ARGS__)
#define print1(msg) printLog(__FUNCTION__, msg)
#define print2(msg, newline) printLog(__FUNCTION__, msg, newline)

using namespace std;

enum LoggerLevel {
	LOGGER_LEVEL_OFF,
	LOGGER_LEVEL_DEBUGGING,
};

class Logger {
	MAKESINGLE(Logger)
public:
	void setLoggerLevel(LoggerLevel level) {
		this->logLevel = level;
	}

	int getFileSize(const string& filename) {
		ifstream file(filename, ios::binary | ios::ate);
		if (!file) {
			// cerr << "Error: Cannot open file " << filename << endl;
			return RETURN_FAIL;
		}

		return static_cast<int>(file.tellg());
	}

	string getDateFromtString() {
		auto now = chrono::system_clock::now();
		auto in_time_t = chrono::system_clock::to_time_t(now);
		tm buf;
		localtime_s(&buf, &in_time_t);

		ostringstream dateTimeStream;
		dateTimeStream << put_time(&buf, "%y%m%d_%Hh%Mm%Ss");

		return dateTimeStream.str();
	}

	int saveUntilLog() {
		string strDatesInfo = getDateFromtString();
		string oldFileName = LOG_FILE_NAME_LATEST;
		string newFileName = "until_" + strDatesInfo + ".log";

		if (rename(oldFileName.c_str(), newFileName.c_str())) {
			// cerr << "Error: Fail to re name" << endl;
			return RETURN_FAIL;
		}
		return RETURN_SUCCESS;
	}

	int modifyLogToZip() {
		string untilLog = "until_*.log";

		vector<string> logFiles;
		WIN32_FIND_DATAA  findFileData;
		HANDLE hFind = FindFirstFileA(untilLog.c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE) return RETURN_FAIL;

		do {
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::string filename = findFileData.cFileName;
				logFiles.push_back(filename);
			}
		} while (FindNextFileA(hFind, &findFileData) != 0);

		FindClose(hFind);

		if (logFiles.size() < MAX_LOG_TO_ZIP) return RETURN_SUCCESS;

		for (int i = 0; i < logFiles.size() - MAX_LOG_TO_ZIP + 1; ++i) {
			string oldFileName = logFiles[i];
			string compressedLogFile = oldFileName;
			compressedLogFile.replace(compressedLogFile.find(".log"), 4, ".zip");
			rename(oldFileName.c_str(), compressedLogFile.c_str());
		}

		return RETURN_SUCCESS;
	}

	int checkLogFileSize(size_t logSize) {
		int logFileSize = getFileSize(LOG_FILE_NAME_LATEST);
		int ret = RETURN_SUCCESS;

		if (logFileSize == RETURN_FAIL) return ret;
		if (logFileSize + logSize >= MAX_LOG_SIZE) {
			ret += saveUntilLog();
			ret += modifyLogToZip();
		}
		return ret;
	}

	int openLogFile(fstream& logFstream, const string& filename) {
		logFstream.open(filename, ios::out | ios::app);
		if (!logFstream.is_open()) return RETURN_FAIL;
		return RETURN_SUCCESS;
	}

	void closeLogFile() {
		logFstream.close();
	}

	void saveLog(string log) {
		checkLogFileSize(log.size());

		if (openLogFile(logFstream, LOG_FILE_NAME_LATEST) == RETURN_FAIL) return;

		logFstream << log << endl;
		closeLogFile();
	}

	void formatLog(string& logString, string funcName, string message) {
		auto now = chrono::system_clock::now();
		auto in_time_t = chrono::system_clock::to_time_t(now);
		tm buf;
		localtime_s(&buf, &in_time_t);

		ostringstream dateTimeStream;
		dateTimeStream << put_time(&buf, "%y.%m.%d %H:%M");

		ostringstream funcNameStream;
		funcNameStream << left << setw(30) << funcName + string("()");

		logString = "[" + dateTimeStream.str() + "] "
			+ funcNameStream.str() + ": "
			+ message;
	}

	void printLog(string funcName, string message) {
		printLog(funcName, message, true);
	}

	void printLog(string funcName, string message, bool addNewline) {
		if (this->logLevel == LOGGER_LEVEL_DEBUGGING) {
			if (addNewline)
				cout << message << endl;
			else
				cout << message;
		}

		string logString;
		formatLog(logString, funcName, message);

		saveLog(logString);
	}

private:
	static constexpr char LOG_FILE_NAME_LATEST[11] = "latest.log";
	static constexpr int MAX_LOG_SIZE = 1024 * 10; // 10KB
	static constexpr int MAX_LOG_TO_ZIP = 2;

	static constexpr int RETURN_SUCCESS = 0;
	static constexpr int RETURN_FAIL = -1;

	LoggerLevel logLevel = LOGGER_LEVEL_DEBUGGING;
	fstream logFstream;
	streampos logFileSize;
};
