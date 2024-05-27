#include "Logger.h"

using namespace std;

void Logger::setLoggerLevel(LoggerLevel level) {
	this->logLevel = level;
}

int Logger::getFileSize(const string& filename) {
	ifstream file(filename, ios::binary | ios::ate);
	if (!file) {
		cerr << "Error: Cannot open file " << filename << endl;
		return -1;
	}
	
	return static_cast<int>(file.tellg());
}

string Logger::getDateFromtString() {
	auto now = chrono::system_clock::now();
	auto in_time_t = chrono::system_clock::to_time_t(now);
	tm buf;
	localtime_s(&buf, &in_time_t);

	ostringstream dateTimeStream;
	dateTimeStream << put_time(&buf, "%y%m%d_%Hh%Mm%Ss");

	return dateTimeStream.str();
}

void Logger::saveUntilLog() {

	string strDatesInfo = getDateFromtString();
	string oldFileName = LOG_FILE_NAME_LATEST;
	string newFileName = "until_" + strDatesInfo + ".log";

	if (!rename(oldFileName.c_str(), newFileName.c_str())) {
		cerr << "Error: Fail to re name" << endl;
	}
}

void Logger::modifyLogToZip() {
	// TODO : log to zip
}

void Logger::checkLogFileSize(size_t logSize) {
	int logFileSize = getFileSize(LOG_FILE_NAME_LATEST);

	if (logFileSize == -1) return;
	if (logFileSize + logSize >= MAX_LOG_SIZE) {
		saveUntilLog();
		modifyLogToZip();
	}
}

bool Logger::openLogFile(fstream& logFstream, const string& filename) {
	logFstream.open(filename, ios::out | ios::app);
	if (!logFstream.is_open()) return false;
	return true;
}

void Logger::closeLogFile() {
	logFstream.close();
}

void Logger::saveLog(string log) {
	if (!openLogFile(logFstream, LOG_FILE_NAME_LATEST)) return;
	
	checkLogFileSize(log.size());
	logFstream << log << endl;
	closeLogFile();
}

void Logger::formatLog(string& logString, string funcName, string message) {
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

void Logger::printLog(string funcName, string message) {
	string logString;
	formatLog(logString, funcName, message);

	if (this->logLevel == LOGGER_LEVEL_DEBUGGING)
		cout << logString << endl;

	saveLog(logString);
}
