#include<iostream>
#include<algorithm>
#include"AVLTreeNode.h"
using namespace std;

class AVLTree
{
private:
	AVLTreeNode *root;
	AVLTreeNode *Search(int,AVLTreeNode *);
	AVLTreeNode *LeftRotate(AVLTreeNode *);
	AVLTreeNode *LeftAndRightRotate(AVLTreeNode *);
	AVLTreeNode *RightRotate(AVLTreeNode *);
	AVLTreeNode *RightAndLeftRotate(AVLTreeNode *);
	int GetHeight(AVLTreeNode *);
	void PreOrderPrint(AVLTreeNode *);
	void InOrderPrint(AVLTreeNode *);
	void SufOrderPrint(AVLTreeNode *);
	void RotatePrint(AVLTreeNode *,int);
	AVLTreeNode *Insert(int,AVLTreeNode *);
	AVLTreeNode *Delete(bool&,int,AVLTreeNode *);
public:
	AVLTree();
	void Insert(int);
	bool Search(int);
	bool Delete(int);
	bool Updata(int,int);
	void PreOrderPrint();
	void InOrderPrint();
	void SufOrderPrint();
	void RotatePrint();
};


AVLTree::AVLTree()
{
	root=NULL;
}

/*********************************************
*参数：当前节点
*返回值：当前节点高度
*功能：返回当前节点高度
**********************************************/
int AVLTree::GetHeight(AVLTreeNode *tempNode)
{
	return NULL==tempNode?-1:tempNode->height;
}

/*********************************************
*参数：待查找元素，当前节点
*返回值：元素所在节点
*功能：返回元素所在节点
**********************************************/
AVLTreeNode *AVLTree::Search(int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return NULL;
	else if(tempKey==tempNode->key)
		return tempNode;
	else if(tempKey<tempNode->key)
		return Search(tempKey,tempNode->leftChild);
	return Search(tempKey,tempNode->rightChild);
}
bool AVLTree::Search(int tempKey)
{
	if(NULL==Search(tempKey,root))
		return false;
	return true;
}

/*********************************************
*参数：当前节点
*返回值：当前子树根节点
*功能：左旋调平衡
**********************************************/
AVLTreeNode *AVLTree::LeftRotate(AVLTreeNode *tempNode)
{
	AVLTreeNode *lChildNode=tempNode->rightChild->leftChild,*newRoot=tempNode->rightChild;
	tempNode->rightChild->leftChild=tempNode;
	tempNode->rightChild=lChildNode;
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(NULL!=tempNode->rightChild)
	tempNode->rightChild->height=max(GetHeight(tempNode->rightChild->leftChild),GetHeight(tempNode->rightChild->rightChild))+1;
	return newRoot;
}

/*********************************************
*参数：当前节点
*返回值：当前子树根节点
*功能：右旋调平衡
**********************************************/
AVLTreeNode *AVLTree::RightRotate(AVLTreeNode *tempNode)
{
	AVLTreeNode *rChildNode=tempNode->leftChild->rightChild,*newRoot=tempNode->leftChild;
	tempNode->leftChild->rightChild=tempNode;
	tempNode->leftChild=rChildNode;
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(NULL!=tempNode->leftChild)
	tempNode->leftChild->height=max(GetHeight(tempNode->leftChild->leftChild),GetHeight(tempNode->leftChild->rightChild))+1;
	return newRoot;
}

/*********************************************
*参数：当前节点
*返回值：当前子树根节点
*功能：先左旋后右旋调平衡
**********************************************/
AVLTreeNode *AVLTree::LeftAndRightRotate(AVLTreeNode *tempNode)
{
	tempNode->leftChild=LeftRotate(tempNode->leftChild);
	return RightRotate(tempNode);
}

/*********************************************
*参数：当前节点
*返回值：当前子树根节点
*功能：先右旋后左旋调平衡
**********************************************/
AVLTreeNode *AVLTree::RightAndLeftRotate(AVLTreeNode *tempNode)
{
	tempNode->rightChild=RightRotate(tempNode->rightChild);
	return LeftRotate(tempNode);
}

/*********************************************
*参数：待插入元素,当前节点
*返回值：当前子树根节点
*功能：插入元素到当前节点的子树
**********************************************/
AVLTreeNode *AVLTree::Insert(int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
	    return tempNode=new AVLTreeNode(tempKey);
	else 
	{
		if(tempKey==tempNode->key)
			return tempNode;
		else if(tempKey<tempNode->key)
			tempNode->leftChild=Insert(tempKey,tempNode->leftChild);
		else tempNode->rightChild=Insert(tempKey,tempNode->rightChild);
	}
	//tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	if(2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
	{
		if(tempKey<tempNode->leftChild->key)
			tempNode=RightRotate(tempNode);
		else tempNode=LeftAndRightRotate(tempNode);
	}
	else if(-2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
	{
		if(tempKey>tempNode->rightChild->key)
			tempNode=LeftRotate(tempNode);
		else tempNode=RightAndLeftRotate(tempNode);
	}
	tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	return tempNode;
}
void AVLTree::Insert(int tempKey)
{
	root=Insert(tempKey,root);
}

/*********************************************
*参数：待删除元素,当前节点
*返回值：当前子树根节点
*功能：删除元素
**********************************************/
AVLTreeNode *AVLTree::Delete(bool &isDelSucceed,int tempKey,AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return NULL;
	else 
	{
		if(tempKey==tempNode->key)
		{
			if(NULL==tempNode->rightChild)
			{
				AVLTreeNode *cur=tempNode;
				tempNode=tempNode->leftChild;
				delete cur;
				isDelSucceed=true;
				return tempNode;
			}
			else//找到右子树最小的元素代替，然后删除 
			{
				AVLTreeNode *cur=tempNode->rightChild;
				while(cur->leftChild!=NULL)
					cur=cur->leftChild;
				tempNode->key=cur->key;
				tempNode->rightChild=Delete(isDelSucceed,cur->key,tempNode->rightChild);
			}
		}
		else if(tempKey<tempNode->key)
			tempNode->leftChild=Delete(isDelSucceed,tempKey,tempNode->leftChild);
		else tempNode->rightChild=Delete(isDelSucceed,tempKey,tempNode->rightChild);

		if(-2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))//删除的是左子树上的
		{
			if(GetHeight(tempNode->rightChild->rightChild)>=GetHeight(tempNode->rightChild->leftChild))
				tempNode=LeftRotate(tempNode);
			else tempNode=RightAndLeftRotate(tempNode);
		}
		else if(2==GetHeight(tempNode->leftChild)-GetHeight(tempNode->rightChild))
		{
			if(GetHeight(tempNode->leftChild->leftChild)>=GetHeight(tempNode->leftChild->rightChild))
				tempNode=RightRotate(tempNode);
			else tempNode=LeftAndRightRotate(tempNode);
		}
		tempNode->height=max(GetHeight(tempNode->leftChild),GetHeight(tempNode->rightChild))+1;
	}
	return tempNode;
}
bool AVLTree::Delete(int tempKey)
{
	bool isDelSucceed=false;
	root=Delete(isDelSucceed,tempKey,root);
	return isDelSucceed;
}

/**********************************************************
*参数：待修改节点元素、修改后的元素
*返回值：返回修改是否成功
*功能：修改函数
************************************************************/
bool AVLTree::Updata(int oldKey,int newKey)
{
	if(Delete(oldKey))
	{
		Insert(newKey);
		return true;
	}
	return false;
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：前序遍历二叉查找树
************************************************************/
void AVLTree::PreOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	cout<<tempNode->key<<"    ";
	PreOrderPrint(tempNode->leftChild);
	PreOrderPrint(tempNode->rightChild);
}
void AVLTree::PreOrderPrint()
{
	PreOrderPrint(this->root);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：中序遍历二叉查找树
************************************************************/
void AVLTree::InOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	InOrderPrint(tempNode->leftChild);
	cout<<tempNode->key<<"   ";
	InOrderPrint(tempNode->rightChild);
}
void AVLTree::InOrderPrint()
{
	InOrderPrint(root);
}

/**********************************************************
*参数：当前子树根节点
*返回值：空
*功能：后序遍历二叉查找树树
************************************************************/
void AVLTree::SufOrderPrint(AVLTreeNode *tempNode)
{
	if(NULL==tempNode)
		return ;
	SufOrderPrint(tempNode->leftChild);
	SufOrderPrint(tempNode->rightChild);
	cout<<tempNode->key<<"    ";
}
void AVLTree::SufOrderPrint()
{
	SufOrderPrint(root);
}

/**********************************************************
*参数：当前子树根节点，缩进列数
*返回值：空
*功能：翻转打印AVL树
************************************************************/
void AVLTree::RotatePrint(AVLTreeNode *tempNode,int tempColumn)
{
	if(NULL==tempNode)
		return ;
	RotatePrint(tempNode->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"---"<<tempNode->key<<endl;
	RotatePrint(tempNode->rightChild,tempColumn+1);
}
void AVLTree::RotatePrint()
{
	RotatePrint(root,0);
}

void Menu()
{
	int val,choice,newVal;
	AVLTree myAVLTree;
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
		myAVLTree.Insert(val);
	}
	else if(2==choice)
	{
		cin>>val;
		if(myAVLTree.Delete(val))
			cout<<"删除成功!"<<endl;
		else cout<<"删除失败!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(myAVLTree.Updata(val,newVal))
			cout<<"修改成功!"<<endl;
		else cout<<"修改失败!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=myAVLTree.Search(val))
			cout<<"查找成功!"<<endl;
		else cout<<"查找失败!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========前序=============="<<endl;
	myAVLTree.PreOrderPrint();
	cout<<endl<<"==========中序================"<<endl;
	myAVLTree.InOrderPrint();
	cout<<endl<<"==========后续==============="<<endl;
	myAVLTree.SufOrderPrint();
	cout<<endl<<"==========对称+旋转==============="<<endl;
	myAVLTree.RotatePrint();
	cout<<endl<<"*****************************"<<endl;
	}
	else return ;
	}
}

int main()
{
	while(true)
		Menu();
	return 0;
}

