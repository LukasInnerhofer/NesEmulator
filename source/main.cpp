#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "libnes/nes.h"

#include "screen_libgraphics.h"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " inesFilePath\n";
		return EXIT_SUCCESS;
	}
	std::string filePath{argv[1]};

	std::shared_ptr<LibGraphics::Window> window{std::make_shared<LibGraphics::Window>("NesEmulator")};
	std::shared_ptr<NesEmulator::ScreenLibGraphics> screen{std::make_shared<NesEmulator::ScreenLibGraphics>(window)};
	LibNes::Nes nes{screen};

	std::ifstream file{filePath, std::ios::in | std::ios::binary | std::ios::ate};

	if(!file.good())
	{
		std::cerr << "Failed to read ines file: " << filePath << "\n";
		return EXIT_FAILURE;
	}
	
	nes.loadCartridge(file);
	nes.reset();

#if defined(NES_EMULATOR_LOG)
	auto log = std::ofstream("nes.log");
#endif

	LibGraphics::Window::Event event;
	while (window)
	{
		nes.runFor(std::chrono::milliseconds(16)
#if defined(NES_EMULATOR_LOG)
			, log
#endif
		);

		screen->draw();
		window->display();
		if (window->pollEvent(event))
		{
			switch(event.type)
			{
			case LibGraphics::Window::EventType::Closed:
				window = nullptr;
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
