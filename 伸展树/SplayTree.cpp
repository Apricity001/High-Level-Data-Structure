#include<iostream>
#include"SplayTreeNode.h"
using namespace std;

class SplayTree
{
private:
	SplayTreeNode *root;
	void LeftRotate(SplayTreeNode *);
	void RightRotate(SplayTreeNode *);
	void Splay(SplayTreeNode *);
	void PreOrderSTPrint(SplayTreeNode *);
	void InOrderSTPrint(SplayTreeNode *);
	void RotateSTPrint(SplayTreeNode *,int);
	void SufOrderSTPrint(SplayTreeNode *);
	void DeleteNoOrOneChildSTNode(SplayTreeNode *,SplayTreeNode *);
public:
	SplayTree();
	void InsertSplayTree(int);
	bool DeleteSplayTree(int);
	bool UpdataSplayTree(int,int);
	SplayTreeNode *FindSplayTree(int);
	void PreOrderSTPrint();
	void InOrderSTPrint();
	void RotateSTPrint();
	void SufOrderSTPrint();
};

SplayTree::SplayTree()
{
	this->root=NULL;
} 

/**************************************************************
*参数：待左旋的节点
*返回值：空
*功能：左旋
***************************************************************/
void SplayTree::LeftRotate(SplayTreeNode *tempSTNode)
{
	SplayTreeNode *rChild=tempSTNode->rightChild;
	if(NULL!=tempSTNode->parent)//不为根节点
	{
		if(tempSTNode->parent->leftChild==tempSTNode)
			tempSTNode->parent->leftChild=rChild;
		else 
			tempSTNode->parent->rightChild=rChild;
	}
	rChild->parent=tempSTNode->parent;
	tempSTNode->parent=rChild;
	if(rChild->leftChild!=NULL)
		rChild->leftChild->parent=tempSTNode;
	tempSTNode->rightChild=rChild->leftChild;
	rChild->leftChild=tempSTNode;
	if(NULL==rChild->parent)
		this->root=rChild;
}

/**************************************************************
*参数：待右旋的节点
*返回值：空
*功能：右旋
***************************************************************/
void SplayTree::RightRotate(SplayTreeNode *tempSTNode)
{
	SplayTreeNode *lChild=tempSTNode->leftChild;
	if(NULL!=tempSTNode->parent)//不为根节点
	{
		if(tempSTNode->parent->rightChild==tempSTNode)
			tempSTNode->parent->rightChild=lChild;
		else 
			tempSTNode->parent->leftChild=lChild;
	}
	lChild->parent=tempSTNode->parent;
	tempSTNode->parent=lChild;
	if(lChild->rightChild!=NULL)
		lChild->rightChild->parent=tempSTNode;
	tempSTNode->leftChild=lChild->rightChild;
	lChild->rightChild=tempSTNode;
	if(NULL==lChild->parent)
		this->root=lChild;
}

/**************************************************************
*参数：待伸展的节点
*返回值：空
*功能：将当前节点伸展的根节点
***************************************************************/
void SplayTree::Splay(SplayTreeNode *tempSTNode)
{
	while(NULL!=tempSTNode&&NULL!=tempSTNode->parent)
	{
		if(tempSTNode->parent->leftChild==tempSTNode)//父亲节点右旋
			RightRotate(tempSTNode->parent);
		else LeftRotate(tempSTNode->parent);
	}
}

/**************************************************************
*参数：带插入元素
*返回值：空
*功能：将当前元素插入伸展树
***************************************************************/
void SplayTree::InsertSplayTree(int tempKey)
{
	SplayTreeNode *pre=NULL,*cur=this->root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey插到左子树
			cur=cur->leftChild;
		else cur=cur->rightChild;//插到左子树
	}
	SplayTreeNode *tempSTNode=new SplayTreeNode(tempKey);
	tempSTNode->parent=pre;
	if(pre==NULL)//若插入的为根节点
	{
		this->root=tempSTNode;
	}
	else if(pre->key>tempSTNode->key)
		pre->leftChild=tempSTNode;
	else pre->rightChild=tempSTNode;
	Splay(tempSTNode);
}

/**************************************************************
*参数：带查找元素
*返回值：返回查找元素在伸展树中的位置
*功能：查找当前元素是否在伸展树
***************************************************************/
SplayTreeNode *SplayTree::FindSplayTree(int tempKey)
{
	SplayTreeNode *cur=this->root;
	while(cur!=NULL)
	{
		if(cur->key==tempKey)
			break;
		else if(cur->key>tempKey)
			cur=cur->leftChild;
		else cur=cur->rightChild;
	}
	Splay(cur);
	return cur;
}

/**********************************************************
*参数：pre待删除节点的父节点，cur待删除节点
*返回值：空
*功能：删除左右孩子有为空的情况
************************************************************/
void SplayTree::DeleteNoOrOneChildSTNode(SplayTreeNode *pre,SplayTreeNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//左右孩子为空
	{
		if(NULL==pre)
			this->root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//若右子树不为空
	{
		if(NULL==pre)
		{
			this->root=cur->rightChild;
			cur->rightChild->parent=NULL;
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
			this->root=cur->leftChild;
			cur->leftChild->parent=NULL;
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
*参数：待删除节点元素
*返回值：空
*功能：删除元素主函数
************************************************************/
bool SplayTree::DeleteSplayTree(int tempKey)
{
	SplayTreeNode *pre=NULL,*cur=root;
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
	{
		DeleteNoOrOneChildSTNode(pre,cur);
		Splay(pre);
	}
	else //左右子树都不为空
	{
		SplayTreeNode *rPre=cur,*rCur=cur->rightChild;//找到右子树最小元素
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;
		DeleteNoOrOneChildSTNode(rPre,rCur);
		Splay(rPre);
	}
	return true;
}

/**********************************************************
*参数：待修改节点元素、修改后的元素
*返回值：返回修改是否成功
*功能：修改函数
************************************************************/
bool SplayTree::UpdataSplayTree(int oldKey,int newKey)
{
	if(DeleteSplayTree(oldKey))
	{
		InsertSplayTree(newKey);
		return true;
	}
	return false;
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：前序遍历二叉查找树
************************************************************/
void SplayTree::PreOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	cout<<tempSTNode->key<<"    ";
	PreOrderSTPrint(tempSTNode->leftChild);
	PreOrderSTPrint(tempSTNode->rightChild);
}
void SplayTree::PreOrderSTPrint()
{
	PreOrderSTPrint(this->root);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：中序遍历二叉查找树
************************************************************/
void SplayTree::InOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	InOrderSTPrint(tempSTNode->leftChild);
	cout<<tempSTNode->key<<"   ";
	InOrderSTPrint(tempSTNode->rightChild);
}
void SplayTree::InOrderSTPrint()
{
	InOrderSTPrint(this->root);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：后序遍历二叉查找树树
************************************************************/
void SplayTree::SufOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	SufOrderSTPrint(tempSTNode->leftChild);
	SufOrderSTPrint(tempSTNode->rightChild);
	cout<<tempSTNode->key<<"    ";
}
void SplayTree::SufOrderSTPrint()
{
	SufOrderSTPrint(this->root);
}

/**********************************************************
*参数：当前子树根节点，缩进列数
*返回值：空
*功能：翻转打印伸展树
************************************************************/
void SplayTree::RotateSTPrint(SplayTreeNode *tempSTNode,int tempColumn)
{
	if(NULL==tempSTNode)
		return ;
	RotateSTPrint(tempSTNode->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"---"<<tempSTNode->key<<endl;
	RotateSTPrint(tempSTNode->rightChild,tempColumn+1);
}
void SplayTree::RotateSTPrint()
{
	RotateSTPrint(this->root,0);
}


void Menu()
{
	int val,choice,newVal;
	SplayTree mySplayTree;
	while(true)
	{
	do
	{
	cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	cout<<"       1.插入"<<endl;
	cout<<"       2.删除"<<endl;
	cout<<"       3.修改"<<endl;
	cout<<"       4.查找"<<endl;
	cout<<"       5.显示"<<endl;
	cout<<"       6.返回"<<endl;
	cout<<"请输入你的选项[ ]\b\b";
	cin>>choice; 
	}while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6);
	if(1==choice)
	{
		cin>>val;
		mySplayTree.InsertSplayTree(val);
	}
	else if(2==choice)
	{
		cin>>val;
		if(mySplayTree.DeleteSplayTree(val))
			cout<<"删除成功!"<<endl;
		else cout<<"删除失败!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(mySplayTree.UpdataSplayTree(val,newVal))
			cout<<"修改成功!"<<endl;
		else cout<<"修改失败!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=mySplayTree.FindSplayTree(val))
			cout<<"查找成功!"<<endl;
		else cout<<"查找失败!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========前序=============="<<endl;
	mySplayTree.PreOrderSTPrint();
	cout<<endl<<"==========中序================"<<endl;
	mySplayTree.InOrderSTPrint();
	cout<<endl<<"==========后续==============="<<endl;
	mySplayTree.SufOrderSTPrint();
	cout<<endl<<"==========对称+旋转==============="<<endl;
	mySplayTree.RotateSTPrint();
	cout<<endl<<"*****************************"<<endl;
	}
	else return ;
	}
}


int main()
{
	while(true)
		 Menu();
	system("pause");
	return 0;
}
