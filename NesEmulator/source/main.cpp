#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>

#include "nes.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " inesFilePath\n";
		return EXIT_SUCCESS;
	}
	std::string filePath{argv[1]};

	LibNes::Nes nes;

	std::ifstream file{filePath, std::ios::in | std::ios::binary | std::ios::ate};

	if(!file.good())
	{
		std::cerr << "Failed to read ines file: " << filePath << "\n";
		return EXIT_FAILURE;
	}
	
	nes.loadCartridge(file);
	nes.reset();

	std::atomic<bool> loop{true};
	std::thread uiThread{[&]()
	{ 
		std::cout << "Running...\n Press return to exit.\n";
		std::cin.get(); 
		loop = false; 
	}};

	while (loop)
	{
		nes.runFor(std::chrono::milliseconds(16));
	}

	uiThread.join();

	return EXIT_SUCCESS;
}
