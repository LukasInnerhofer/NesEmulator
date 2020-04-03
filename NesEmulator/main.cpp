#include <fstream>

#include "nes.h"

int main()
{
	Nes nes;

	std::ifstream file;
	file.open(R"(H:\Emulators\NES\Roms\Super_mario_brothers.nes)", std::ios::in | std::ios::binary | std::ios::ate);

	nes.loadCartridge(file);
	return 0;
}