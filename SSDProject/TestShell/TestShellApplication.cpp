#include "Command.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

class TestShellApplication {
public:
	void run(void) {
		while (true) {
			string input = getUserCommand();

			try {
				vector<string> v = trim(input);

				if (v.front() == "exit" || v.size() == 0 )
					break;

				Command* cmd = createCommandInstance(v.front());

				if (cmd != nullptr)
					executeCommand(cmd, v);
				else
					cout << "invalid command, try again" << endl;
			}
			catch (std::exception e) {
				cout << e.what() << endl;
			}
		};
	}

	int executeCommand(Command* cmd, vector<string>& v) {
		return cmd->execute(v);
	}

private:

	string getUserCommand() {
		string result;
		cout << "$ ";
		getline(cin, result);
		return result;
	}

	Command* createCommandInstance(const string& cmd) {

		if (cmd == "write") {
//			return new WriteCommand();
		}
		else if (cmd == "read") {
//			return new ReadCommand();
		}
		else if (cmd == "help") {
//			return new HelpCommand();
		}
		else if (cmd == "fullread") {
//			return new FullReadCommand();
		}
		else if (cmd == "fullwrite") {
//			return new FullWriteCommand();
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
};