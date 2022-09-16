#include<iostream>
using namespace std;

struct BinarySearchTreeNode
{
	int key;
	BinarySearchTreeNode *leftChild;
	BinarySearchTreeNode *rightChild;
	BinarySearchTreeNode(int tempKey)
	{
		key=tempKey;
		leftChild=NULL;
		rightChild=NULL;
	}
};
