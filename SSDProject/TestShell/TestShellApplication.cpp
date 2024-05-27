#include "Command.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

#include "TestApp1Command.cpp"
#include "TestApp2Command.cpp"
#include "HelpCommand.cpp"
#include "FullReadCommand.cpp"
#include "FullWriteCommand.cpp"
#include "ReadCommand.cpp"
#include "WriteCommand.cpp"
using namespace std;

class TestShellApplication {
public:
	void run() {
		bool exit = false;
		do {
			string input = getUserCommand();
			exit = execute(input);
		} while (exit);
	}

	bool execute(string input) {
		try {
			vector<string> v = trim(input);

			if (v.front() == "exit" || v.size() == 0)
				return false;

			Command* cmd = createCommandInstance(v.front());

			if (cmd != nullptr)
				executeCommand(cmd, v);
			else
				logger.print("INVALID COMMAND, TRY AGAIN");				
		}
		catch (std::exception e) {
			cout << e.what() << endl;
			throw e;
		}

		return true;
	}

	void executeCommand(Command* cmd, vector<string>& v) {
		cmd->execute(v);
	}

private:

	string getUserCommand() {
		string result;
		cout << "$ ";
		getline(cin, result);
		return result;
	}

	Command* createCommandInstance(const string& cmd) {
		Receiver receiver;
		if (cmd == "write") {
			return new WriteCommand(&receiver);
		}
		else if (cmd == "read") {
			return new ReadCommand(&receiver);
		}
		else if (cmd == "help") {
			return new HelpCommand(&receiver);
		}
		else if (cmd == "fullread") {
			return new FullReadCommand(&receiver);
		}
		else if (cmd == "fullwrite") {
			return new FullWriteCommand(&receiver);
		}
		else if (cmd == "testapp1") {
			return new TestApp1Command();
		}
		else if (cmd == "testapp2") {
			return new TestApp2Command();
		}
		return nullptr;
	}

	vector<string> trim(const string& str) {
		stringstream ss(str);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> vstrings(begin, end);

		return vstrings;
	}

	Logger& logger = Logger::getInstance();
};