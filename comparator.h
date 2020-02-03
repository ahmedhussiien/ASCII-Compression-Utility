#ifndef __COMPARATOR_H_
#define __COMPARATOR_H_

#include"Node.h"

//Comparator for implementing Min Heap using priority queue
class comparator
{
public:
	int operator () (Node*& n1, Node*& n2);
};

#endif