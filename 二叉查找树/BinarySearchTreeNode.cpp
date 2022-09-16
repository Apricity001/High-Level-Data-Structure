#include<iostream>
#include"BinarySearchTreeNode.h"
using namespace std;

class BinarySearchTree
{
private:
	BinarySearchTreeNode *Root;
public:
	BinarySearchTree();
	BinarySearchTreeNode *GetRoot();
	BinarySearchTreeNode *FindBST(int );
	void UpdataBSTNode(int,int);
	void InsertBSTNode(int);
	bool DeleteBSTNode(int);
	void DeleteNoOrOneChildBSTNode(BinarySearchTreeNode *,BinarySearchTreeNode *);
	void PreOrderBSTPrint(BinarySearchTreeNode *);
	void InOrderBSTPrint(BinarySearchTreeNode *);
	void SufOrderBSTPrint(BinarySearchTreeNode *);
	void RotateBSTPrint(BinarySearchTreeNode *,int);
};

BinarySearchTree::BinarySearchTree()
{
	Root=NULL;
}

/**********************************************************
*参数：无
*返回值：空
*功能：返回二叉查找树根节点
************************************************************/
BinarySearchTreeNode *BinarySearchTree::GetRoot()
{
	return this->Root;
}

/**********************************************************
*参数：待查找值
*返回值：若找到则返回所在节点，否则返回NULL
*功能：插入新结点
************************************************************/
BinarySearchTreeNode *BinarySearchTree::FindBST(int tempKey)
{
	BinarySearchTreeNode *cur=this->Root;
	while(cur!=NULL)
	{
		if(cur->key==tempKey)
			break;
		else if(cur->key>tempKey)
			cur=cur->leftChild;
		else cur=cur->rightChild;
	}
	return cur;
}

/**********************************************************
*参数：待插入值
*返回值：空
*功能：插入新结点
************************************************************/
void BinarySearchTree::InsertBSTNode(int tempKey)
{
	BinarySearchTreeNode *pre=NULL,*cur=this->Root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey插到左子树
			cur=cur->leftChild;
		else cur=cur->rightChild;//插到左子树
	}
	BinarySearchTreeNode *tempNode=new BinarySearchTreeNode(tempKey);
	if(pre==NULL)//若插入的为根节点
	{
		this->Root=tempNode;
	}
	else if(pre->key>tempNode->key)
		pre->leftChild=tempNode;
	else pre->rightChild=tempNode;
}



/**********************************************************
*参数：待修改数值oldKey,修改后的数值newKey
*返回值：空
*功能：更新节点元素
************************************************************/
void BinarySearchTree::UpdataBSTNode(int oldKey,int newKey)
{
	DeleteBSTNode(oldKey);
	InsertBSTNode(newKey);
}

/**********************************************************
*参数：pre待删除节点的父节点，cur待删除节点
*返回值：空
*功能：删除左右孩子有为空的情况
************************************************************/
void BinarySearchTree::DeleteNoOrOneChildBSTNode(BinarySearchTreeNode *pre,BinarySearchTreeNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//左右孩子为空
	{
		if(NULL==pre)
			Root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//若右子树不为空
	{
		if(NULL==pre)
			Root=cur->rightChild;
		else if(pre->leftChild==cur)
			pre->leftChild=cur->rightChild;
		else 
			pre->rightChild=cur->rightChild;
		delete cur;
	}
	else if(cur->leftChild!=NULL)//若左子树不为空
	{
		if(NULL==pre)
			Root=cur->leftChild;
		else if(pre->leftChild==cur)
			pre->leftChild=cur->leftChild;
		else
			pre->rightChild=cur->leftChild;
		delete cur;
	}
}


/**********************************************************
*参数：待删除节点元素
*返回值：空
*功能：删除元素主函数
************************************************************/
bool BinarySearchTree::DeleteBSTNode(int tempKey)
{
	BinarySearchTreeNode *pre=NULL,*cur=Root;
	while(cur!=NULL)//寻找待删除元素
	{
		if(cur->key==tempKey)
			break;
		else
		{
			pre=cur;
			if(cur->key>tempKey)
				cur=cur->leftChild;
			else cur=cur->rightChild;
		}
	}
	if(NULL==cur)return false;
	if(NULL==cur->leftChild||NULL==cur->rightChild)
		DeleteNoOrOneChildBSTNode(pre,cur);
	else //左右子树都不为空
	{
		BinarySearchTreeNode *rPre=cur,*rCur=cur->rightChild;//找到右子树最小元素
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;
		DeleteNoOrOneChildBSTNode(rPre,rCur);
	}
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：前序遍历二叉查找树
************************************************************/
void BinarySearchTree::PreOrderBSTPrint(BinarySearchTreeNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	cout<<tempRoot->key<<"    ";
	PreOrderBSTPrint(tempRoot->leftChild);
	PreOrderBSTPrint(tempRoot->rightChild);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：中序遍历二叉查找树
************************************************************/
void BinarySearchTree::InOrderBSTPrint(BinarySearchTreeNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	InOrderBSTPrint(tempRoot->leftChild);
	cout<<tempRoot->key<<"    ";
	InOrderBSTPrint(tempRoot->rightChild);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：后序遍历二叉查找树树
************************************************************/
void BinarySearchTree::SufOrderBSTPrint(BinarySearchTreeNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	SufOrderBSTPrint(tempRoot->leftChild);
	SufOrderBSTPrint(tempRoot->rightChild);
	cout<<tempRoot->key<<"    ";
}

/**********************************************************
*参数：当前子树根节点，缩进列数
*返回值：空
*功能：翻转打印二叉查找树
************************************************************/
void BinarySearchTree::RotateBSTPrint(BinarySearchTreeNode *tempRoot,int tempColumn)
{
	if(NULL==tempRoot)
		return ;
	RotateBSTPrint(tempRoot->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"---"<<tempRoot->key<<endl;
	RotateBSTPrint(tempRoot->rightChild,tempColumn+1);
}

int main()
{
	int val;
	while(true)
	{
		BinarySearchTree myBinarySearchTree;
		while(cin>>val)
		{
			if(val==0)break;
			myBinarySearchTree.InsertBSTNode(val);
		}
		cout<<endl<<"*****************************"<<endl;
		myBinarySearchTree.PreOrderBSTPrint(myBinarySearchTree.GetRoot());
		cout<<endl<<"============================="<<endl;
		myBinarySearchTree.InOrderBSTPrint(myBinarySearchTree.GetRoot());
		cout<<endl<<"============================="<<endl;
		myBinarySearchTree.SufOrderBSTPrint(myBinarySearchTree.GetRoot());
		cout<<endl<<"============================="<<endl;
		myBinarySearchTree.RotateBSTPrint(myBinarySearchTree.GetRoot(),0);
		cout<<endl<<"*****************************"<<endl;
		while(cin>>val)
		{
			if(!val)break;
			myBinarySearchTree.DeleteBSTNode(val);
			cout<<endl<<"*****************************"<<endl;
			myBinarySearchTree.PreOrderBSTPrint(myBinarySearchTree.GetRoot());
			cout<<endl<<"============================="<<endl;
			myBinarySearchTree.InOrderBSTPrint(myBinarySearchTree.GetRoot());
			cout<<endl<<"============================="<<endl;
			myBinarySearchTree.SufOrderBSTPrint(myBinarySearchTree.GetRoot());
			cout<<endl<<"============================="<<endl;
			myBinarySearchTree.RotateBSTPrint(myBinarySearchTree.GetRoot(),0);
			cout<<endl<<"*****************************"<<endl;
		}
	}
	system("pause");
	return 0;
}
