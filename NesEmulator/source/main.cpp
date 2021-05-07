#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#include "nes.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		return EXIT_SUCCESS;
	}
	std::string filePath { argv[1] };

	Nes nes;

	std::ifstream file;
	file.open(filePath, std::ios::in | std::ios::binary | std::ios::ate);

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
