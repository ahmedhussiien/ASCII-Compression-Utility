#ifndef __HUFFMAN_CODER_H_
#define __HUFFMAN_CODER_H_
#define EOFCHR 'Á' //Non ASCII character written at the end of the file
#define Compress 1
#define Decompress 0

#include<iostream>
#include<fstream>
#include<string>
#include<map>

#include"MinHeap.h"
#include"BitWriter.h"
#include"BitReader.h"
using namespace std;

class HuffmanCoder
{
	map<char, string> CharacterCodes; //Contains each character with the corrosponding Huffman code
	string Input;
	string Output;
	int TotalNumOfChar;
	Node* HuffmanTreeTop;
	Node* CurrIndex; //Used in Huffman tree traversal

	///Utility functions
	void GetCharactersProbabilities(map<char, int>& CharacterProbabilities); //Counts number of characters in the input file
	Node* ConstructHuffmanTree(map<char, int>& CharacterProbabilities);
	void GetCodes(Node* root, int code[], int index);

	int SaveCompressedFile(ofstream& OutputFile, ifstream& InputFile);
	int SaveDecompressedFile(ofstream& OutputFile, ifstream& InputFile);

	float ComputeCompressionRatio(map<char, int>& CharacterProbabilities);
	float ComputeCompressionEfficiency(map<char, int>& CharacterProbabilities);

	//Header contains number of code characters followed by each character with it's corrosponding frequency
	int WriteHeader(ofstream& OutputFile, map<char, int>& CharacterProbabilities);
	int ReadHeader(ifstream& InputFile, map<char, int>& CharacterProbabilities);

	//Traverse CharacterCodes tree till it finds a leaf node
	bool TraverseTree(int Bit, char& ReturnedChar);

public:
	
	HuffmanCoder(bool function, string inputPath, string outputPath); //@param function = 1 for compression, = 0 for Decompression
	HuffmanCoder(string inputPath, string outputPath);
	HuffmanCoder();
	void setInput(string inputPath);
	void setOutput(string outputPath);

	int CompressFile();
	int DecompressFile();
};

#endif