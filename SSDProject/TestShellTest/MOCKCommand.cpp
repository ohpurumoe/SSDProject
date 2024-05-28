#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../TestShell/Command.h"

using namespace testing;
using namespace std;

class MockReceiver : public IReceiver {
public:
	MOCK_METHOD(void, write, (int), (override));
	MOCK_METHOD(void, read, (int), (override));
	MOCK_METHOD(void, erase, (int), (override));
	MOCK_METHOD(void, fullwrite, (), (override));
	MOCK_METHOD(void, fullread, (), (override));
	MOCK_METHOD(int, getResultCode, (), (override));
	MOCK_METHOD(void, setResultCode, (int), (override));
	MOCK_METHOD(void, mock, (), ());
};

// Mock Receiver class
class MockCommand : public Command {
public:
	MockCommand(MockReceiver* receiver) : receiver_(receiver) {}
	void execute(vector<string> v) override {
		if (receiver_ == nullptr) {
			cout << "receiver_ is nullptr" << endl;
			return;
		}
		receiver_->mock();
		// TODO : something
		return;
	}

	MOCK_METHOD(int, read, (int lba), ());
	MOCK_METHOD(void, write, (int lba, string data), ());

private:
	MockReceiver* receiver_;
};

