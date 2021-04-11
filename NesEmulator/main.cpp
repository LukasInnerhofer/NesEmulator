#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#include "nes.h"

int main()
{
	std::cin.get();

	{

		Nes nes;

		std::ifstream file;
		file.open(R"(C:\Users\lukas\OneDrive\Emulators\NES\Debug\test.nes)", std::ios::in | std::ios::binary | std::ios::ate);

		nes.loadCartridge(file);
		nes.reset();

#if 0
		while (true)
		{
			nes.step();
		}
#endif
		std::cin.get();

		nes.reset();
	}

	{

		Nes nes;

		std::ifstream file;
		file.open(R"(C:\Users\lukas\OneDrive\Emulators\NES\Debug\test.nes)", std::ios::in | std::ios::binary | std::ios::ate);

		nes.loadCartridge(file);
		nes.reset();

#if 0
		while (true)
		{
			nes.step();
		}
#endif
		std::cin.get();

		nes.reset();
	}

	std::cin.get();

	return 0;
}