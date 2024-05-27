#include "TestShellApplication.cpp"
#include <fstream>

class ShellRunner {
public:
	ShellRunner(TestShellApplication* app) :
		app(app) {}

	void run(string filename) {
		ifstream file;

		file.open(filename);
		string read;
		while (file.peek() != EOF) {
			getline(file, read);
			cout << "read : " << read << endl;

			app->execute(read);
		}
	}

private:
	string getStringToCommand(const string &str) {
		if (str == "FullWriteReadCompare" )
			return "testapp1";
		else if (str == "FullRead10AndCompare")
			return "testapp2";
		else if (str == "Write10AndCompare")
			return "testapp3";
		else if (str == "Loop_WriteAndReadCompare")
			return "testapp4";

		return "";
	}
private:

	TestShellApplication * app;
};