#include "util.h"
#include "SSD.cpp"

int main(int argc, char** argv) {
	auto command_args_pair = parse(argc, argv);
	auto hardware = new SSD();
	StorageDriver driver(hardware);
	execute(driver, command_args_pair);
	delete hardware;
	
	return 0;
}
