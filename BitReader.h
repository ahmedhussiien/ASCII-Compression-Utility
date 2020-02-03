#ifndef __BIT_READER_H_
#define __BIT_READER_H_
using namespace std;

#include<fstream>
#include<iostream>

class BitReader
{
	ifstream* InputFile;
	char* buffer;
	int bit;
	int currentBit;
public:
	BitReader(ifstream& Ifile);
	void GetNextBits();
	int ReadNextBit(); //Return bit by bit from each byte from right to left
};

#endif
