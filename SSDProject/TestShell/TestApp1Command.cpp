#include "Command.h"
#include <fstream>

using namespace std;

class TestApp1Command : public Command {
public:
	// Command을(를) 통해 상속됨
	void execute(vector<string> v) override
	{
		// full write
		if (v.size() >= 2)
			throw invalid_argument("invalid vector size");

		for (int i = 0; i < 100; i++) {
			string argument = "W";
			argument += " " + to_string(i);
			argument += " 0x5A5A5A5A";
			if (invoke(argument)) {
				throw invalid_argument("invoke error");
			}
		}
		
		// full read
		ifstream ifs;
		string result;
		for (int i = 0; i < 100; i++) {
			string argument = "R " + to_string(i);
			if (invoke(argument)) {
				cout << "invoke error" << endl;
				throw invalid_argument("invoke error");
			}

			ifs.open(ssdResult);
			result = string((std::istreambuf_iterator<char>(ifs)),
				std::istreambuf_iterator<char>());
			cout << result << endl;
			ifs.close();
		}
	}

private:
	const std::string ssdResult = ".\\result.txt";
};