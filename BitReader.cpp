#include "BitReader.h"

BitReader::BitReader(ifstream& Ifile): InputFile(&Ifile), currentBit(8), bit(0)
{
	buffer = new char; //Allocating buffer of size Char
}

void BitReader::GetNextBits()
{
	currentBit = 0;
	InputFile->read(buffer, sizeof(char));;
}

int BitReader::ReadNextBit()
{
	if (currentBit == 8) {
		InputFile->read(buffer, sizeof(char));
		currentBit = 0;
	}
	
	bit = ((*buffer >> currentBit) & 1);
	currentBit++;
	return bit;
}
