﻿#include <fstream>
#include "..\TestShell\Command.h"
using namespace std;

class TestApp2Command : public Command {
public:
	TestApp2Command(IReceiver* receiver) : Command(receiver) {}

	// Command을(를) 통해 상속됨
	void execute(vector<string> v) override
	{
		int ret = 0;
		// full write
		for (int i = 0; i < 5; i++) {
			string argument = "W";
			argument += " " + to_string(i);
			argument += " 0xAAAABBBB";
			for (int j = 0; j < 30; j++)
				if (invoke(argument)) {
					throw invalid_argument("invoke error");
				}
		}

		for (int i = 0; i < 5; i++) {
			string argument = "W";
			argument += " " + to_string(i);
			argument += " 0x12345678";
			if (invoke(argument)) {
				logger.print("invoke error");
				throw invalid_argument("invoke error");
			}
		}

		ifstream ifs;
		for (int i = 0; i < 5; i++) {
			string argument = "R " + to_string(i);
			string result;

			if (invoke(argument)) {
				logger.print("invoke error");
				throw invalid_argument("invoke error");
			}

			ifs.open(ssdResult);
			result = string((std::istreambuf_iterator<char>(ifs)),
				std::istreambuf_iterator<char>());

			if ("0x12345678" != result)
				ret++;

			logger.print(result);
			ifs.close();
		}

		receiver->setResultCode(ret);
	}

private:
	const std::string ssdResult = ".\\result.txt";
};