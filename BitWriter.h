#ifndef __BIT_WRITER_H_
#define __BIT_WRITER_H_
using namespace std;

#include<fstream>
#include<iostream>

class BitWriter
{
	char bitBuffer;
	int currentBit;
	ofstream* OutputFile;

public:
	BitWriter(ofstream& Ofile);
	void WriteBit(int bit); //Sent bit by bit from right to left
	//Flush bits after writing data
	void FlushBits();
};

#endif