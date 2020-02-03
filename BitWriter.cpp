#include "BitWriter.h"


BitWriter::BitWriter(ofstream& Ofile): OutputFile(&Ofile), currentBit(0), bitBuffer(0)
{
}

void BitWriter::WriteBit(int bit)
{
	if (bit)
		bitBuffer |= (1 << currentBit);

	currentBit++;
	if (currentBit == 8)
	{
		*OutputFile << bitBuffer;
		currentBit = 0;
		bitBuffer = 0;
	}
}

void BitWriter::FlushBits()
{
	while (currentBit)
		WriteBit(0);
}
