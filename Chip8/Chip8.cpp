#include <cstdint>
#include <fstream>
#include "Chip8.h"



Chip8::Chip8()
{
	//initialise le pc
	pc = Chip8::START_ADDRESS;
	
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




