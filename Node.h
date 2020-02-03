#ifndef __NODE_H_
#define __NODE_H_

class Node
{
private:
	char data;
	int frequency;
	Node* Left;
	Node* Right;

public:
	Node(char val, int freq);

	void setData(char val);
	void setFrequency(int val);
	void setLeft(Node* p);
	void setRight(Node* p);

	int getFrequency() const;
	char getData() const;
	Node* getRight() const;
	Node* getLeft() const;
	bool isLeaf() const;
};

#endif