#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class InputValidChecker {
public:
	static const int TYPE_CMD = 0;
	static const int TYPE_CMD_LBA = 1;
	static const int TYPE_CMD_LBA_VAL = 2;

	bool check(std::vector<std::string> args, int type = TYPE_CMD) {
		if (args.empty()) {
			return false;
		}

		if (type == TYPE_CMD) {
			return (args.size() == 1);
		}

		if (type == TYPE_CMD_LBA)
			return (args.size() == 2) && isValidLBA(args[1]);

		if (type == TYPE_CMD_LBA_VAL) {
			return (args.size() == 3) && isValidLBA(args[1]) && isValidValue(args[2]);
		}

		return false;
	}

private:
	bool isValidLBA(const string lba) {
		int num = -1;

		try {
			num = stoi(lba);
		}
		catch (...) {
			return false;
		}

		return num >= 0 && num <= 99;
	}

	bool isValidValue(const string value) {

		if (value.substr(0, 2) != "0x") {
			return false;
		}

		string hexValue = value.substr(2);
		for (char c : hexValue) {
			if (!((c >= 'A' && c <= 'F') || (c >= '0' && c <= '9'))) {
				return false;
			}
		}

		return true;
	}


};