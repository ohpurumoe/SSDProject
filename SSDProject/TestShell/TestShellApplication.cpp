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

		if (v[0] == "w") {
			return new WriteCommand(v[1], v[2]);
		}
		else if (v[0] == "r") {
			return new ReadCommand(v[1]);
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