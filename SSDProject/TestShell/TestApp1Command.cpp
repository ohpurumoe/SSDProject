#include "Command.h"

using namespace std;

class TestApp1Command : public Command {
public:
	// Command을(를) 통해 상속됨
	void execute(vector<string> v) const override
	{
		// full write
		for (int i = 0; i < 100; i++) {
			string argument = "w";
			argument += " " + to_string(i);
			argument += " 0x5A5A5A5A";
			cout << argument << endl;
			if (!invoke(argument)) {
				cout << "invoke error" << endl;
			}
		}

		// full read
		for (int i = 0; i < 100; i++) {
			string argument = "r " + to_string(i);
			if (!invoke(argument)) {
				cout << "invoke error" << endl;
			}
		}
	
		// TODO : verify
		
	}
};