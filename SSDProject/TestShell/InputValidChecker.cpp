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
		return false;
	}

private:
	bool isValidLBA(const string lba) {
		return false;
	}

	bool isValidValue(const string value) {
		return false;
	}
};