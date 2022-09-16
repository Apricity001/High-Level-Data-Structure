#include<iostream>
using namespace std;

/**********************************
*功能:防止头文件多次包含
**********************************/
#ifndef SPLAYTREENODE_H
#define SPLAYTREENODE_H

class SplayTreeNode
{
public:
	SplayTreeNode *leftChild;
	SplayTreeNode *rightChild;
	SplayTreeNode *parent;
	int key;
	SplayTreeNode(int key)
	{
		this->key=key;
		this->leftChild=NULL;
		this->rightChild=NULL;
		this->parent=NULL;
	}
};

#endif SPLAYTREENODE_H
