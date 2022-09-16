#include<iostream>
using namespace std;

class BinaryHeapNode
{
private:
	int key;
	int degree;
	BinaryHeapNode* parent;
	BinaryHeapNode* leftChild;
	BinaryHeapNode* brother;
public:
	BinaryHeapNode();
	BinaryHeapNode(int,int,BinaryHeapNode*,BinaryHeapNode*,BinaryHeapNode*);
	BinaryHeapNode(BinaryHeapNode &);
	BinaryHeapNode& operator=(BinaryHeapNode &);
	int GetKey();
	void SetKey(int);
	int GetDegree();
	void SetDegree(int);
	BinaryHeapNode* GetParent();
	void SetParent(BinaryHeapNode*);
	BinaryHeapNode* GetLeftChild();
	void SetLeftChild(BinaryHeapNode*);
	BinaryHeapNode* GetBrother();
	void SetBrother(BinaryHeapNode*);
};


BinaryHeapNode::BinaryHeapNode()
{
	this->key=0;
	this->degree=0;
	this->parent=NULL;
	this->leftChild=NULL;
	this->brother=NULL;
}

BinaryHeapNode::BinaryHeapNode(int tempKey,int tempDegree,BinaryHeapNode* tempParent,BinaryHeapNode* tempLeftChild,BinaryHeapNode* tempBrother)
{
	this->key=tempKey;
	this->degree=tempDegree;
	this->parent=tempParent;
	this->leftChild=tempLeftChild;
	this->brother=tempBrother;
}

BinaryHeapNode::BinaryHeapNode(BinaryHeapNode &tempBinaryHeapNode)
{
	this->key=tempBinaryHeapNode.GetKey();
	this->degree=tempBinaryHeapNode.GetDegree();
	this->parent=tempBinaryHeapNode.GetParent();
	this->leftChild=tempBinaryHeapNode.GetLeftChild();
	this->brother=tempBinaryHeapNode.GetBrother();
}


BinaryHeapNode& BinaryHeapNode::operator=(BinaryHeapNode &tempBinaryHeapNode)
{
	if(this==&tempBinaryHeapNode)//排除自赋值
		return *this;
	delete this->parent;
	delete this->leftChild;
	delete this->brother;
	this->key=tempBinaryHeapNode.GetKey();
	this->degree=tempBinaryHeapNode.GetDegree();
	this->parent=tempBinaryHeapNode.GetParent();
	this->leftChild=tempBinaryHeapNode.GetLeftChild();
	this->brother=tempBinaryHeapNode.GetBrother();
	return *this;
}

int BinaryHeapNode::GetKey()
{
	return this->key;
}

void BinaryHeapNode::SetKey(int tempKey)
{
	 this->key=tempKey;
}

int BinaryHeapNode::GetDegree()
{
	return this->degree;
}

void BinaryHeapNode::SetDegree(int tempDegree)
{
	 this->degree=tempDegree;
}


BinaryHeapNode* BinaryHeapNode::GetParent()
{
	return this->parent;
}

void BinaryHeapNode::SetParent(BinaryHeapNode* tempParent)
{
	this->parent=tempParent;
}

BinaryHeapNode* BinaryHeapNode::GetLeftChild()
{
	return this->leftChild;
}

void BinaryHeapNode::SetLeftChild(BinaryHeapNode* tempLeftChild)
{
	this->leftChild=tempLeftChild;
}


BinaryHeapNode* BinaryHeapNode::GetBrother()
{
	return this->brother;
}

void BinaryHeapNode::SetBrother(BinaryHeapNode* tempBrother)
{
	this->brother=tempBrother;
}
