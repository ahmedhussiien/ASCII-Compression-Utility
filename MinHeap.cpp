#include "MinHeap.h"
#include <stdlib.h>

MinHeap::MinHeap()
{
}

MinHeap::MinHeap(char* Data, int* Freq, int length)
{
	for (int i = 0; i < length; i++) {
		Values.push(new Node(Data[i], Freq[i]));
	}
}

void MinHeap::insert(char data, int frequency)
{
	Values.push(new Node(data, frequency));
}

void MinHeap::insert(Node* N)
{
	Values.push(N);
}

int MinHeap::getSize() const
{
	return Values.size();
}

Node* MinHeap::getMin() const
{
	return Values.top();
}

void MinHeap::DeleteMin()
{
	Values.pop();
}

Node* MinHeap::popMin()
{
	Node* temp = Values.top();
	Values.pop();
	return temp;
}



