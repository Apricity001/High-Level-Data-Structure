#include<iostream>
#include"RedBlackNode.h"
using namespace std;

class RedBlackTree
{
private:
	RedBlackNode *Root;
public:
	RedBlackTree();
	RedBlackNode *GetRoot();
	RedBlackNode *FindRB(int );
	void UpdataRBNode(int,int);
	void InsertRBNode(int);
	void InsertFixUp(RedBlackNode *);
	void LeftRotate(RedBlackNode *);
	void RightRotate(RedBlackNode *);
	void DeleteFixUp(RedBlackNode *);
	bool DeleteRBNode(int);
	void DeleteNoOrOneChildNode(RedBlackNode *,RedBlackNode *);
	void PreOrderPrint(RedBlackNode *);
	void InOrderPrint(RedBlackNode *);
	void SufOrderPrint(RedBlackNode *);
	void RotatePrint(RedBlackNode *,int);
};

RedBlackTree::RedBlackTree()
{
	Root=NULL;
}

/**********************************************************
*参数：无
*返回值：空
*功能：返回红黑树根节点
************************************************************/
RedBlackNode *RedBlackTree::GetRoot()
{
	return this->Root;
}

/**********************************************************
*参数：待插入值
*返回值：空
*功能：插入新结点
************************************************************/
void RedBlackTree::InsertRBNode(int tempKey)
{
	RedBlackNode *pre=NULL,*cur=this->Root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey插到左子树
			cur=cur->leftChild;
		else cur=cur->rightChild;//插到左子树
	}
	RedBlackNode *tempNode=new RedBlackNode(tempKey);
	tempNode->parent=pre;
	if(pre==NULL)//若插入的为根节点
	{
		this->Root=tempNode;
	}
	else if(pre->key>tempNode->key)
		pre->leftChild=tempNode;
	else pre->rightChild=tempNode;
	
	InsertFixUp(tempNode);//保持红黑树性质
}

/**********************************************************
*参数：待查找值
*返回值：若找到则返回所在节点，否则返回NULL
*功能：插入新结点
************************************************************/
RedBlackNode *RedBlackTree::FindRB(int tempKey)
{
	RedBlackNode *cur=this->Root;
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
*参数：待修改数值oldKey,修改后的数值newKey
*返回值：空
*功能：更新节点元素
************************************************************/
void RedBlackTree::UpdataRBNode(int oldKey,int newKey)
{
	DeleteRBNode(oldKey);
	InsertRBNode(newKey);
}

/**********************************************************
*参数：当前节点
*返回值：空
*功能：左旋
************************************************************/
void RedBlackTree::LeftRotate(RedBlackNode *tempNode)
{
	RedBlackNode *rChildNode=tempNode->rightChild;
	if(rChildNode->leftChild!=NULL)//左子树的右子树不为空
		rChildNode->leftChild->parent=tempNode;
	rChildNode->parent=tempNode->parent;
	if(NULL==tempNode->parent)//当前节点为根节点
		this->Root=rChildNode;
	else if(tempNode==tempNode->parent->leftChild)
		tempNode->parent->leftChild=rChildNode;
	else tempNode->parent->rightChild=rChildNode;
	tempNode->parent=rChildNode;
	tempNode->rightChild=rChildNode->leftChild;
	rChildNode->leftChild=tempNode;
}

/**********************************************************
*参数：当前节点
*返回值：空
*功能：右旋
************************************************************/
void RedBlackTree::RightRotate(RedBlackNode *tempNode)
{
	RedBlackNode *lChildNode=tempNode->leftChild;
	if(lChildNode->rightChild!=NULL)//左子树的右子树不为空
		lChildNode->rightChild->parent=tempNode;
	lChildNode->parent=tempNode->parent;
	if(NULL==tempNode->parent)//当前节点为根节点
		this->Root=lChildNode;
	else if(tempNode==tempNode->parent->leftChild)
		tempNode->parent->leftChild=lChildNode;
	else tempNode->parent->rightChild=lChildNode;
	tempNode->parent=lChildNode;
	tempNode->leftChild=lChildNode->rightChild;
	lChildNode->rightChild=tempNode;
}

/**********************************************************
*参数：当前插入节点
*返回值：空
*功能：在插入节点后加以调整保持红黑树性质
************************************************************/
void RedBlackTree::InsertFixUp(RedBlackNode *tempNode)
{
	RedBlackNode *parTempNode=tempNode->parent,*ancleTempNode;
	while(parTempNode!=NULL&&RED==parTempNode->color)//父节点不为空且为红色
	{
		if(parTempNode->parent!=NULL)
		{
			if(parTempNode->parent->leftChild==parTempNode)
			{
				ancleTempNode=parTempNode->parent->rightChild;
				if(ancleTempNode!=NULL&&RED==ancleTempNode->color)//叔叔节点为红色
				{
					parTempNode->color=BLACK;
					ancleTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					tempNode=parTempNode->parent;//指向爷爷节点
					parTempNode=tempNode->parent;
				}
				else 
				{
					if(tempNode==parTempNode->rightChild)
					{
						LeftRotate(parTempNode);
						tempNode=tempNode->leftChild;
						parTempNode=tempNode->parent;
					}
					parTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					RightRotate(parTempNode->parent);
					break;
				}
			}
			else 
			{
				ancleTempNode=parTempNode->parent->leftChild;
				if(ancleTempNode!=NULL&&RED==ancleTempNode->color)//叔叔节点为红色
				{
					parTempNode->color=BLACK;
					ancleTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					tempNode=parTempNode->parent;//指向爷爷节点
					parTempNode=tempNode->parent;
				}
				else{
					if(tempNode==parTempNode->leftChild)
					{
						RightRotate(parTempNode);
						tempNode=tempNode->rightChild;
						parTempNode=tempNode->parent;
					}
					parTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					LeftRotate(parTempNode->parent);
					break;
				}
			}
		}
		else break;
	}
	this->Root->color=BLACK;
}

/**********************************************************
*参数：pre待删除节点的父节点，cur待删除节点
*返回值：空
*功能：删除左右孩子有为空的情况
************************************************************/
void RedBlackTree::DeleteNoOrOneChildNode(RedBlackNode *pre,RedBlackNode *cur)
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
		{
			Root=cur->rightChild;
			Root->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		else 
		{
			pre->rightChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		delete cur;
	}
	else if(cur->leftChild!=NULL)//若左子树不为空
	{
		if(NULL==pre)
		{
			Root=cur->leftChild;
			Root->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		else
		{
			pre->rightChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		delete cur;
	}
}

/**********************************************************
*参数：向上调平衡起点
*返回值：空
*功能：删除元素后调平衡
************************************************************/
void RedBlackTree::DeleteFixUp(RedBlackNode *tempNode)
{
	if(RED==tempNode->color)
		InsertFixUp(tempNode);
}

/**********************************************************
*参数：待删除节点元素值
*返回值：空
*功能：删除某元素值
************************************************************/
bool RedBlackTree::DeleteRBNode(int tempKey)
{
	RedBlackNode *pre=NULL,*cur=Root;
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
	RedBlackNode *tempChild;
	bool tempColor;
	if(NULL==cur->leftChild||NULL==cur->rightChild)
	{
		if(NULL==cur->leftChild)//右孩子存在
			tempChild=cur->rightChild;
		else tempChild=cur->leftChild;
		tempColor=cur->color;
		DeleteNoOrOneChildNode(pre,cur);
		if(tempChild!=NULL&&BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
	else //左右子树都不为空
	{
		RedBlackNode *rPre=cur,*rCur=cur->rightChild;//找到右子树最小元素
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;
		tempChild=rCur->rightChild;//肯定无左孩子
		tempColor=rCur->color;
		DeleteNoOrOneChildNode(rPre,rCur);
		if(tempChild!=NULL&&BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
	
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：前序遍历红黑树
************************************************************/
void RedBlackTree::PreOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"红）  ";
	else cout<<"黑)  ";
	PreOrderPrint(tempRoot->leftChild);
	PreOrderPrint(tempRoot->rightChild);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：中序遍历红黑树
************************************************************/
void RedBlackTree::InOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	InOrderPrint(tempRoot->leftChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"红）  ";
	else cout<<"黑)  ";
	InOrderPrint(tempRoot->rightChild);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：后序遍历红黑树
************************************************************/
void RedBlackTree::SufOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	SufOrderPrint(tempRoot->leftChild);
	SufOrderPrint(tempRoot->rightChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"红）  ";
	else cout<<"黑)  ";
}

/**********************************************************
*参数：当前子树根节点，缩进列数
*返回值：空
*功能：翻转打印二叉查找树
************************************************************/
void RedBlackTree::RotatePrint(RedBlackNode *tempRoot,int tempColumn)
{
	if(NULL==tempRoot)
		return ;
	RotatePrint(tempRoot->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"红）";
	else cout<<"黑)";
	cout<<endl;
	RotatePrint(tempRoot->rightChild,tempColumn+1);
}

int main()
{
	int val;
	while(true)
	{
		RedBlackTree myRedBlackTree;
		while(cin>>val)
		{
			if(val==0)break;
			myRedBlackTree.InsertRBNode(val);
		}
		cout<<endl<<"*****************************"<<endl;
		cout<<endl<<"=============前序============="<<endl;
		myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"=============中序============="<<endl;
		myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============后序============="<<endl;
		myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============对称+顺时针旋转============="<<endl;
		myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
		cout<<endl<<"============================="<<endl;
		cout<<"*****************************"<<endl;
		while(cin>>val)
		{
			if(!val)break;
			myRedBlackTree.DeleteRBNode(val);
			cout<<endl<<"*****************************"<<endl;
			cout<<endl<<"=============前序============="<<endl;
			myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"=============中序============="<<endl;
			myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"==============后序============="<<endl;
			myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"==============对称+顺时针旋转============="<<endl;
			myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
			cout<<endl<<"============================="<<endl;
			cout<<"*****************************"<<endl;
		}
	}
	system("pause");
	return 0;
}
