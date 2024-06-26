﻿#include "Logger.cpp"
#include "TestShellApplication.cpp"
#include <fstream>

class ShellRunner {
public:
	ShellRunner(TestShellApplication* app) :
		app(app) {}

	void run(string filename) {
		ifstream file;
		bool result = false;
		file.open(filename);
		string read;
		while (file.peek() != EOF) {
			getline(file, read);
			string cmd = getStringToCommand(read);
			prepare(read);
			if (cmd.length() != 0) {
				result = app->execute(cmd);
				result &= !(app->getLastResult());
			}

			unprepare(result);
		}
	}

private:
	void prepare(const string &str) {
		logger.print(str + " --- Run...", false);
		oldCoutStreamBuf = std::cout.rdbuf();
		cout.rdbuf(strCout.rdbuf());
	}

	void unprepare(bool result) {
		cout.rdbuf(oldCoutStreamBuf);
		strCout.clear();
		logger.print(result ? "PASS" : "FAIL");
	}

	string getStringToCommand(const string &str) {
		if (str == "FullWriteReadCompare" )
			return "testapp1";
		else if (str == "FullRead10AndCompare")
			return "testapp2";
		else if (str == "Write10AndCompare")
			return "testapp3";
		else if (str == "Loop_WriteAndReadCompare")
			return "testapp4";

		return "";
	}
private:
	streambuf* oldCoutStreamBuf;
	ostringstream strCout;
	TestShellApplication * app;

	Logger& logger = Logger::getInstance();
};