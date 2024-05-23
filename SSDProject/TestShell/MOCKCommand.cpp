#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TestShell/Command.h"

using namespace testing;
using namespace std;

// Mock Receiver class
class MockCommand : public Command {
public:
	MockCommand(Receiver* receiver) : receiver_(receiver) {}
	void execute(vector<string> v) const override {
		if (receiver_ != nullptr)
			receiver_->mock();
		else
			cout << "receiver_ is nullptr" << endl;
	}

	MOCK_METHOD(int, read, (int lba), ());
	MOCK_METHOD(void, write, (int lba, string data), ());

private:
	Receiver* receiver_;
};
