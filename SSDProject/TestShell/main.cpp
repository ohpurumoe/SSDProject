#include "ShellRunner.cpp"

int main(int argc, char* argv[]) {

	string file;

	if (argc > 1) {
		file = argv[1];

		ShellRunner runner(new TestShellApplication());
		runner.run(argv[1]);
	} 
	else {
		TestShellApplication app;
		app.run();
	}

	return 0;
}