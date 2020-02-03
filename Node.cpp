#include "Node.h"

Node::Node(char val, int freq)
{
	this->data = val;
	this->frequency = freq;
	this->Left = nullptr;
	this->Right = nullptr;
}

void Node::setData(char val)
{
	this->data = val;
}

void Node::setFrequency(int val)
{
	this->frequency = val;
}

void Node::setLeft(Node* p)
{
	Left = p;
}

void Node::setRight(Node* p)
{
	Right = p;
}

int Node::getFrequency() const
{
	return this->frequency;
}

char Node::getData() const
{
	return this->data;
}

Node* Node::getRight() const
{
	return Right;
}

Node* Node::getLeft() const
{
	return Left;
}

bool Node::isLeaf() const
{
	if (!Left && !Right)
		return true;
	else
		return false;
}
