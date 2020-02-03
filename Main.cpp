#pragma once
#include <iostream>
#include"HuffmanCoder.h"
using namespace std;

int main() {

	string input = "test999words";
	string output = "compressed";

	HuffmanCoder HCcoder(Compress, input, output);
	HuffmanCoder HCdecoder(Decompress, output, "decompressed");

	return 0;
}