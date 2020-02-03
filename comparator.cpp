#include "comparator.h"

int comparator::operator()(Node*& n1, Node*& n2)
{
	return n1->getFrequency() > n2->getFrequency();
}
