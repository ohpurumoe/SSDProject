#include <string>
#include <iostream>

#include "TestApp1Command.cpp"
#include "TestApp2Command.cpp"

#include "TestShellScenario.h"
using namespace std;

Command* getScenario(const string& str, IReceiver * receiver)
{
	if (str == "testapp1") {
		return new TestApp1Command(receiver);
	}
	else if (str == "testapp2") {
		return new TestApp2Command(receiver);
	}

	return nullptr;
}
