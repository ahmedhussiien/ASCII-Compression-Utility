#ifndef __MINHEAP_H_
#define __MINHEAP_H_
#include<queue>
#include<map>
#include"Node.h"
#include"comparator.h"
using namespace std;

class MinHeap
{
private:
	priority_queue<Node*, vector<Node*>, comparator> Values;

public:
	MinHeap();

	//Constructs MinHeap from two arrays one for data and one for frequency
	MinHeap(char* Data, int* Freq, int length);

	void insert(char data, int frequency);
	void insert(Node* N);

	void DeleteMin();
	Node* popMin();

	int getSize() const;
	Node* getMin() const;
};

#endif