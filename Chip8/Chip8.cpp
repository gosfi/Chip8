#include <cstdint>
#include <fstream>
#include "Chip8.h"

	Chip8::Chip8():randGen(std::chrono::system_clock::now().time_since_epoch().count())
	{
		//initialise le pc
		pc = Chip8::START_ADDRESS;
	
		// charge les polices dans la mémoire
		for (unsigned int i = 0; i < FONTSET_SIZE; i++)
		{
			memory[FONTSET_START_ADDRESS + i] = fontset[i];
		}

		//Initialise le RNG
		randByte =std::uniform_int_distribution<uint8_t>(0,255U);
	}

Chip8::~Chip8()
{
}

void Chip8::LoadROM(char const* filename)
{
	//Ouvre le fichier en tant que stream binaire et bouge le pointeur du fichier à la fin
	std::ifstream file(filename, std::ios::binary | std::ios::ate);

	if(file.is_open())
	{
		// trouve la grosseure du fichier et alloue un buffer pour contenir le contenue du fichier
		std::streampos size = file.tellg();
		char* buffer = new char[size];

		// retourne au debut du fichier et remplis le buffer
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		// charge le contenu de la ROM dans la m/moire du chip8 en commencant par 0x200
		for(long i = 0; i < size; i++)
		{
			Chip8::memory[Chip8::START_ADDRESS + i] = buffer[i];		
		}

		// libere le buffer
		delete[] buffer;
	}
}

//clear screen
void Chip8::OP_00E0()
{
	memset(video, 0, sizeof video);
}

//return from a subroutine
void Chip8::OP_00EE()
{
	--sp;
	pc = stack[sp];
}

//jump to location
void Chip8::OP_1nnn()
{
	uint16_t address = opcode & 0x0FFFu;

	pc = address;
}




