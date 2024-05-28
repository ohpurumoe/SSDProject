#include "SSD.cpp"
#include "Parser.h"

int main(int argc, char** argv) {
	auto hardware = new SSD();
	StorageDriver driver(hardware);
	Parser parser(&driver);

	try {
		auto command_args_pair = parser.parse(argc, argv);
		auto& command = command_args_pair.first;
		auto& args = command_args_pair.second;
		command->execute(args);
	}
	catch (...) {
		std::cout << "Wrong use of SSD.exe. Please retry." << std::endl;
		delete hardware;
		return -1;
	}
	delete hardware;
	
	return 0;
}
