#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#include "nes.h"

int main()
{
	Nes nes;

	std::ifstream file;
	file.open(R"(LibMos6502\test\test.nes)", std::ios::in | std::ios::binary | std::ios::ate);

	if(!file.good())
	{
		return EXIT_FAILURE;
	}
	
	nes.loadCartridge(file);
	nes.reset();

	while (true)
	{
		nes.step();
	}

	return 0;
}