#include "HuffmanCoder.h"

bool HuffmanCoder::TraverseTree(int Bit, char& ReturnedChar)
{
	if (Bit == 0)
		CurrIndex = CurrIndex->getLeft();

	else if (Bit == 1)
		CurrIndex = CurrIndex->getRight();

	if (CurrIndex && CurrIndex->isLeaf()) {
		ReturnedChar = CurrIndex->getData();
		CurrIndex = HuffmanTreeTop;
		return true;
	}
	return false;
}

HuffmanCoder::HuffmanCoder(bool function, string inputPath, string outputPath) : Input(inputPath), Output(outputPath), HuffmanTreeTop(nullptr),
CurrIndex(nullptr), TotalNumOfChar(0)
{
	if (function)
		CompressFile();
	else
		DecompressFile();

}

HuffmanCoder::HuffmanCoder(string inputPath, string outputPath): Input(inputPath), Output(outputPath), HuffmanTreeTop(nullptr),
CurrIndex(nullptr), TotalNumOfChar(0)
{

}

HuffmanCoder::HuffmanCoder(): Input(""), Output(""), HuffmanTreeTop(nullptr), CurrIndex(nullptr), TotalNumOfChar(0)
{
}

void HuffmanCoder::setInput(string inputPath)
{
	Input = inputPath;
}

void HuffmanCoder::setOutput(string outputPath)
{
	Output = outputPath;
}

void HuffmanCoder::GetCharactersProbabilities(map<char, int>& CharacterProbabilities)
{
	ifstream InputFile(Input + ".txt");

	if (!InputFile.is_open()) {
		cout << "No such a file, enter new file name:" << endl;
		return;
	}

	char ch;
	while (InputFile) {
		InputFile.get(ch);
		CharacterProbabilities[ch]++;
		TotalNumOfChar++; //Used in calculating efficiency
	}
	CharacterProbabilities[ch]--; //Input file reads the last character twice
}

Node* HuffmanCoder::ConstructHuffmanTree(map<char, int>& CharacterProbabilities)
{
	//Step1: Creating MinHeap of all characters
	MinHeap* HuffmanTree = new MinHeap();
	map<char, int >::iterator itr;
	for (itr = CharacterProbabilities.begin(); itr != CharacterProbabilities.end(); itr++) {
		HuffmanTree->insert(itr->first, itr->second);
	}
	//Inserting EOF character in the tree
	HuffmanTree->insert(EOFCHR, 1);

	//Step2: Createing a new tree whose root has a weight equal to the sum of the weights T1 + T2
	Node* Left, * Right, * top;
	while (HuffmanTree->getSize() > 1) {
		Left = HuffmanTree->popMin();
		Right = HuffmanTree->popMin();

		//'$' is used as a special character NOTE: it's used to fill the data only
		top = new Node('$', Left->getFrequency() + Right->getFrequency());
		top->setLeft(Left);
		top->setRight(Right);

		//Repeat untill a single tree is constructed
		HuffmanTree->insert(top);
	}

	return HuffmanTree->popMin();
}

void HuffmanCoder::GetCodes(Node* root, int code[], int index)
{
	// Append 0 to left edges
	if (root->getLeft()) {
		code[index] = 0;
		GetCodes(root->getLeft(), code, index + 1);
	}

	// Append 1 for right edges 
	if (root->getRight()) {
		code[index] = 1;
		GetCodes(root->getRight(), code, index + 1);
	}

	if (root->isLeaf()) {
		//Getting the code back as binary from the array
		string codeBinary;
		for (int i = 0; i < index; ++i) {
			codeBinary.append(to_string(code[i]));
		}
		CharacterCodes[root->getData()] = codeBinary;
	}
}

int HuffmanCoder::SaveCompressedFile(ofstream& OutputFile, ifstream& InputFile)
{
	//Writing the file
	char ch;
	string code;
	int bit;
	int currentBit = 0;
	BitWriter bw(OutputFile);

	while (InputFile) {
		InputFile.get(ch);
		if (InputFile.eof()) break; //If it reached the end of the file

		//Writing bit by bit
		code = CharacterCodes[ch];
		for (int i = 0; i < code.size(); i++) { 
			bit = (int)code[i] - '0'; //( '1' to 1, '0' to 0 )
			bw.WriteBit(bit);
		}

	}

	//Writing EOFCHR
	code = CharacterCodes[EOFCHR];
	for (int i = 0; i < code.size(); i++) {
		bit = (int)code[i] - 48;
		bw.WriteBit(bit);
	}

	bw.FlushBits(); //Flush bits after writing all the data
	return 0;
}

int HuffmanCoder::SaveDecompressedFile(ofstream& OutputFile, ifstream& InputFile)
{
	CurrIndex = HuffmanTreeTop;
	BitReader BR(InputFile);
	char decodedChar;
	int bit;
	while (InputFile) {
		bit = BR.ReadNextBit();
		if (TraverseTree(bit, decodedChar)) {
			if (decodedChar == EOFCHR)
				return 0;

			OutputFile << decodedChar;
		}

	}
	return 1;
}

float HuffmanCoder::ComputeCompressionRatio(map<char, int>& CharacterProbabilities)
{
	if (CharacterCodes.size() == 0) return 0;

	float Avglength = 0;

	map<char, string>::iterator itr;
	for (itr = CharacterCodes.begin(); itr != CharacterCodes.end(); itr++) {
		Avglength += CharacterCodes[itr->first].size();
	}
	
	Avglength /= CharacterCodes.size();
	return float(Avglength) / 8;
}

float HuffmanCoder::ComputeCompressionEfficiency(map<char, int>& CharacterProbabilities)
{
	float Entropy = 0;
	float Avglength = 0;
	float probability = 0;

	map<char, int>::iterator itr;
	for (itr = CharacterProbabilities.begin(); itr != CharacterProbabilities.end(); itr++) {
		if (itr->first == EOFCHR)
			continue;	//Do not count the EOF character

		probability = (float)(itr->second) / (float)TotalNumOfChar;
		Avglength += CharacterCodes[itr->first].size();
		Entropy += (probability *  -log2(probability));
	}

	Avglength /= CharacterCodes.size();
	return Entropy / Avglength;
}

int HuffmanCoder::WriteHeader(ofstream& OutputFile, map<char, int>& CharacterProbabilities)
{
	BitWriter bw(OutputFile);
	string code;
	map<char, int >::iterator itr;

	OutputFile << CharacterProbabilities.size() << " ";

	for (itr = CharacterProbabilities.begin(); itr != CharacterProbabilities.end(); itr++) {
		OutputFile << itr->first;
		OutputFile << itr->second << " ";
	}

	return 0;
}

int HuffmanCoder::ReadHeader(ifstream& InputFile, map<char, int>& CharacterProbabilities)
{
	CharacterCodes.clear();
	int numOfcharacters = 0;
	int frequency = 0; 
	char ch;

	InputFile >> numOfcharacters;
	char temp; //used to discard spaces
	InputFile.get(temp);

	string code = "";
	for (int i = 0; i < numOfcharacters; i++) {
		InputFile.get(ch);
		InputFile >> frequency;
		InputFile.get(temp);
		CharacterProbabilities[ch] = frequency;
	}
	return 0;
}

int HuffmanCoder::DecompressFile()
{
	//Check for path
	if (Input == "" || Output == "") {
		cout << "Enter valid path!";
		return 1; //Error
	}

	ifstream InputFile(Input + ".HC", ios::in | ios::binary);
	ofstream OutputFile(Output + ".txt", ios::out);

	if (!OutputFile.is_open() || !InputFile.is_open()) {
		cout << "Failed  to save the file !" << endl;
		return 1;
	}

	map<char, int> CharacterProbabilities;
	ReadHeader(InputFile, CharacterProbabilities);
	HuffmanTreeTop = ConstructHuffmanTree(CharacterProbabilities);
	int arr[20];
	int index = 0;
	GetCodes(HuffmanTreeTop, arr, index);
	SaveDecompressedFile(OutputFile, InputFile);

	cout << "Decompression completed successfully!";
	InputFile.close();
	OutputFile.close();
	
	return 0;
}

int HuffmanCoder::CompressFile()
{
	map<char, int> CharacterProbabilities;
	GetCharactersProbabilities(CharacterProbabilities);
	HuffmanTreeTop = ConstructHuffmanTree(CharacterProbabilities);
	int arr[20];
	int index = 0;
	GetCodes(HuffmanTreeTop, arr, index);

	//Check for path
	if (Input == "" || Output == "") {
		cout << "Enter valid path!";
		return 1; //Error
	}

	//Writing the file
	ofstream OutputFile(Output + ".HC", ios::out | ios::binary);
	ifstream InputFile(Input + ".txt");

	if (!OutputFile.is_open() || !InputFile.is_open()) {
		cout << "Failed  to save the file !" << endl;
		return 1;
	}

	WriteHeader(OutputFile, CharacterProbabilities);
	SaveCompressedFile(OutputFile, InputFile);

	double compressionRatio = ComputeCompressionRatio(CharacterProbabilities);
	cout << "Compression Ratio: " << compressionRatio << endl;
	cout << "Compression Efficiency: " << ComputeCompressionEfficiency(CharacterProbabilities) << endl;

	InputFile.close();
	OutputFile.close();
	return 0;
}
