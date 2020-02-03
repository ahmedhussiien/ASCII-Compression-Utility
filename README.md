# ASCII Compression Utility
## Objective
ASCII files can be compressed by using variable-length Huffman Coding. By analyzing the
different probabilities of the various symbols that occur in a given file, we can build a Huffman
tree to come up with a minimal, optimized binary list of code words for these symbols.

This tool does just that. It compresses and decompresses ASCII-encoded files using Huffman encoding.
Moreover, it calculates the compression ratio and the efficiency of the encoding.

## Example
```C
#include"HuffmanCoder.h"
#define input "test999words"
#define output "compressed"

int main() {

	HuffmanCoder HCcoder(Compress, input, output);
	HuffmanCoder HCdecoder(Decompress, output, "decompressed");

	return 0;
}
```
* The first line of code in the main function compresses the input file "test999words.txt" to the output file "compressed.HC", after that it outputs the compression ratio and efficiency.
* The second line just decompresses "compressed.HC" file.
* Note that the tool can only decompress files that are compressed by the tool itself.
* Note that the second line is independent of the first line. Both can be separated to different programs.

