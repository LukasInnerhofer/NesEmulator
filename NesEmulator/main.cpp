#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#include "nes.h"

int main()
{
	Nes nes;

	std::ifstream file;
	file.open(R"(C:\Users\lukas\OneDrive\Emulators\NES\Debug\test.nes)", std::ios::in | std::ios::binary | std::ios::ate);

	nes.loadCartridge(file);
	nes.reset();

	while (true)
	{
		nes.step();
	}

	return 0;
}