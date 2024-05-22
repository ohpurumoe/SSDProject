#include "Command.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

class TestShellApplication {
public:
	void run(void) {
		string input;
		while (true) {
			cout << "$";
			cin >> input;
			try {
				Command* cmd = parse(input);
				if (cmd == nullptr) {
					cout << "Bye !~" << endl;
					break;
				}
			}
			catch (std::exception e) {
				cout << e.what() << endl;
			}
		};
	}

private:
	Command* parse(const string& str) {
		vector<string> v = trim(str);
		string cmd = v.front();
		if (cmd == "write") {
			return new WriteCommand(v);
		}
		else if (cmd == "read") {
			return new ReadCommand(v);
		}
		else if (cmd == "help") {
			return new HelpCommand(v);
		}
		else if (cmd == "fullread") {
			return new FullReadCommand(v);
		}
		else if (cmd == "fullwrite") {
			return new FullWriteCommand(v);
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