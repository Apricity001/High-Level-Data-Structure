#include<iostream>
#include"BinaryHeapNode.h"
using namespace std;

class BinaryHeap
{
private:
	BinaryHeapNode *headBinaryHeap;
public:
	void InitiateBinHeap();
	void LinkBinHeap(BinaryHeapNode *,BinaryHeapNode *);
	BinaryHeapNode *GetMinElement();
	BinaryHeapNode *GetHeadBinHeap();
	void SetHeadBinHeap(BinaryHeapNode *);
	BinaryHeapNode *InsertBinHeap(int);
	BinaryHeapNode *MergeBinHeap(BinaryHeapNode *);
	BinaryHeapNode *UnionBinHeap();
	BinaryHeapNode *DeleteMinElement();
	bool DeleteElement(int);
	BinaryHeapNode *UpdateBinHeap(int,int);
	BinaryHeapNode *FindElement(BinaryHeapNode *,int);
};

/**************************************************
*参数:无
*返回值：无
*功能:实例化头结点
***************************************************/
void BinaryHeap::InitiateBinHeap()
{
	headBinaryHeap=new BinaryHeapNode;
}

/**************************************************
*参数:无
*返回值：返回值小关键字所在节点
*功能:寻找二项堆中的最小关键字
***************************************************/
BinaryHeapNode *BinaryHeap::GetMinElement()
{
	if(NULL==headBinaryHeap)
		return NULL;
	int minKey=1<<30;
	BinaryHeapNode *minPtr=NULL,*cur=headBinaryHeap->GetBrother();
	while(cur!=NULL)
	{
		if(cur->GetKey()<minKey)
		{
			minPtr=cur;
			minKey=cur->GetKey();
		}
		cur=cur->GetBrother();
	}
	return minPtr;
}

BinaryHeapNode *BinaryHeap::GetHeadBinHeap()
{
	return this->headBinaryHeap;
}

void BinaryHeap::SetHeadBinHeap(BinaryHeapNode *tempHead)
{
	this->headBinaryHeap=tempHead;
}

/**************************************************
*参数:分别表示2个二项堆的根节点
*返回值：无
*功能:将oneBinHeap并成otherBinHeap的左孩子
***************************************************/
void BinaryHeap::LinkBinHeap(BinaryHeapNode *oneBinHeap,BinaryHeapNode *otherBinHeap)
{
	oneBinHeap->SetParent(otherBinHeap);
	oneBinHeap->SetBrother(otherBinHeap->GetLeftChild());
	otherBinHeap->SetLeftChild(oneBinHeap);
	otherBinHeap->SetDegree(otherBinHeap->GetDegree()+1);
}

/**************************************************
*参数:表示待合并二项堆的根节点
*返回值：新二项堆的根节点
*功能:按节点度递增的顺序合并2个二项堆
***************************************************/
BinaryHeapNode *BinaryHeap::MergeBinHeap(BinaryHeapNode *otherBinHeapHead)
{
	BinaryHeapNode *pA=headBinaryHeap->GetBrother(),*pB=otherBinHeapHead->GetBrother(),*retHead=NULL,*pC=NULL;
	bool isFirst=true;
	while(pA!=NULL&&pB!=NULL)
	{
		if(pA->GetDegree()<pB->GetDegree())
		{
			if(isFirst)
			{
				retHead=pA;
				pC=retHead;
				isFirst=false;
			}
			else 
			{
				pC->SetBrother(pA);
				pC=pC->GetBrother();
			}
			pA=pA->GetBrother();
		}
		else 
		{
			if(isFirst)
			{
				retHead=pB;
				pC=retHead;
				isFirst=false;
			}
			else 
			{
				pC->SetBrother(pB);
				pC=pC->GetBrother();
			}
			pB=pB->GetBrother();
		}
	}
	while(pA!=NULL)
	{
		if(isFirst)
		{
			retHead=pA;
			pC=retHead;
			isFirst=false;
		}
		else 
		{
			pC->SetBrother(pA);
			pC=pC->GetBrother();
		}
		pA=pA->GetBrother();
	}
	while(pB!=NULL)
	{
		if(isFirst)
		{
			retHead=pB;
			pC=retHead;
			isFirst=false;
		}
		else 
		{
			pC->SetBrother(pB);
			pC=pC->GetBrother();
		}
		pB=pB->GetBrother();
	}

	headBinaryHeap->SetBrother(retHead);
	return headBinaryHeap;
}


/**************************************************
*参数:无
*返回值：无
*功能:合并相邻的度数相等的二叉树
***************************************************/
BinaryHeapNode *BinaryHeap::UnionBinHeap()
{
	if(NULL==headBinaryHeap||NULL==headBinaryHeap->GetBrother())
		return headBinaryHeap;

	BinaryHeapNode *pre=NULL,*cur=headBinaryHeap->GetBrother(),*next=cur->GetBrother(),*retHead=cur;
	while(next!=NULL)
	{
		if((cur->GetDegree()!=next->GetDegree())||(next->GetBrother()!=NULL&&cur->GetDegree()==next->GetBrother()->GetDegree()))
		{
			pre=cur;
			cur=next;//cur->GetBrother();
		}
		else
		{
			if(cur->GetKey()<next->GetKey())
			{
				cur->SetBrother(next->GetBrother());
				LinkBinHeap(next,cur);
			}
			else 
			{

				if(NULL==pre)retHead=next;
				else pre->SetBrother(next);
				LinkBinHeap(cur,next);
				cur=next;
			}
		}
		next=next->GetBrother();
	}
	headBinaryHeap->SetBrother(retHead);
	return headBinaryHeap;
}

/**************************************************
*参数:带插入的关键字
*返回值：新二项堆的根节点
*功能:插入单个关键字
***************************************************/
BinaryHeapNode *BinaryHeap::InsertBinHeap(int tempKey)
{
	BinaryHeap tempBinHeap;
	tempBinHeap.InitiateBinHeap();
	BinaryHeapNode *retHead,*tempBinHeapHead=tempBinHeap.GetHeadBinHeap();
	BinaryHeapNode *tempNode=new BinaryHeapNode(tempKey,0,NULL,NULL,NULL);
	tempBinHeapHead->SetBrother(tempNode);
	if(NULL==this->headBinaryHeap)retHead=tempBinHeap.GetHeadBinHeap();
	else
	{
		retHead=tempBinHeap.MergeBinHeap(this->headBinaryHeap);
		this->SetHeadBinHeap(retHead);
		retHead=this->UnionBinHeap();
	}
	return retHead;
}

/**************************************************
*参数:无
*返回值：无
*功能:删除最小关键字
***************************************************/
BinaryHeapNode *BinaryHeap::DeleteMinElement()
{
	if(NULL==headBinaryHeap)
		return NULL;
	int minKey=1<<30;
	BinaryHeapNode *minPrePtr=NULL,*minPtr=NULL,*pre=headBinaryHeap,*cur=headBinaryHeap->GetBrother();
	while(cur!=NULL)
	{
		if(cur->GetKey()<minKey)
		{
			minPrePtr=pre;
			minPtr=cur;
			minKey=cur->GetKey();
		}
		pre=cur;
		cur=cur->GetBrother();
	}
	if(NULL==minPrePtr)
		return headBinaryHeap;
	minPrePtr->SetBrother(minPtr->GetBrother());
	BinaryHeap tempBinHeap;
	tempBinHeap.InitiateBinHeap();
	BinaryHeapNode *q,*p=minPtr->GetLeftChild();
	while(p!=NULL)
	{
		q=p->GetBrother();
		p->SetBrother(NULL);
		p->SetParent(NULL);
		BinaryHeapNode *tempHeadBinaryHeap=new BinaryHeapNode;
		tempHeadBinaryHeap->SetBrother(p);
		tempBinHeap.SetHeadBinHeap(tempBinHeap.MergeBinHeap(tempHeadBinaryHeap));
		p=q;
	}
	tempBinHeap.SetHeadBinHeap(tempBinHeap.UnionBinHeap());
	this->SetHeadBinHeap(this->MergeBinHeap(tempBinHeap.GetHeadBinHeap()));
	this->SetHeadBinHeap(this->UnionBinHeap());

	if(NULL!=minPtr)delete minPtr;
	return this->GetHeadBinHeap();
}

/**************************************************
*参数:分别表示待查找二项树的根节点，待查找关键字
*返回值：待查找关键字所在节点
*功能:查找关键字所在节点
***************************************************/
BinaryHeapNode *BinaryHeap::FindElement(BinaryHeapNode *tempHead,int tempKey)
{
	BinaryHeapNode *q=NULL,*p=tempHead;
	while(p!=NULL)
	{
		if(p->GetKey()==tempKey)
			return p;
		else 
		{
			q=FindElement(p->GetLeftChild(),tempKey);
			if(NULL!=q)
				return q;
			p=p->GetBrother();
		}
	}
	return NULL;
}

/**************************************************
*参数:分别表示更新前和更新后的关键字
*返回值：更新后关键字所在节点
*功能:将某个关键字更新为另一个
***************************************************/
BinaryHeapNode *BinaryHeap::UpdateBinHeap(int oldKey,int newKey)
{
	BinaryHeapNode *next,*pre,*cur=FindElement(headBinaryHeap->GetBrother(),oldKey);
	if(NULL==cur)
		return NULL;
	cur->SetKey(newKey);
	if(oldKey>newKey)
	{
		pre=cur->GetParent();
		while(pre!=NULL&&pre->GetKey()>cur->GetKey())
		{
			int temp=pre->GetKey();
			pre->SetKey(cur->GetKey());
			cur->SetKey(temp);
			cur=pre;
			pre=pre->GetParent();
		}
		return cur;
	}
	else if(oldKey<newKey)
	{

		BinaryHeapNode *minPtr;
		int minKey;
		while(cur->GetLeftChild()!=NULL)
		{
			minKey=1<<30;
			minPtr=NULL;
			next=cur->GetLeftChild();
			while(next!=NULL)
			{
				if(next->GetKey()<newKey&&next->GetKey()<minKey)
				{
					minKey=next->GetKey();
					minPtr=next;
				}
				next=next->GetBrother();
			}
			if(minPtr!=NULL)
			{
				cur->SetKey(minPtr->GetKey());
				cur=minPtr;
			}
			else 
			{
				cur->SetKey(newKey);
				return cur;
			}
		}
	}
}

/**************************************************
*参数:表示待删除关键字
*返回值：是否删除成功
*功能:删除某个给定关键字
***************************************************/
bool BinaryHeap::DeleteElement(int tempKey)
{
	if(NULL==UpdateBinHeap(tempKey,-(1<<30)))
		return false;
	this->DeleteMinElement();
	return true;
}


int main()
{
	int n;
	BinaryHeap myBinaryHeap;
	myBinaryHeap.InitiateBinHeap();
	while(cin>>n)
	{
		if(-1==n)break;
		myBinaryHeap.SetHeadBinHeap(myBinaryHeap.InsertBinHeap(n));
	}

	BinaryHeap myBinaryHeap2;
	myBinaryHeap2.InitiateBinHeap();
	while(cin>>n)
	{
		if(-1==n)break;
		myBinaryHeap2.SetHeadBinHeap(myBinaryHeap2.InsertBinHeap(n));
	}

	myBinaryHeap2.SetHeadBinHeap(myBinaryHeap2.MergeBinHeap(myBinaryHeap.GetHeadBinHeap()));
	myBinaryHeap.SetHeadBinHeap((myBinaryHeap2.UnionBinHeap()));


	BinaryHeapNode *ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;
	int oldKey=45,newKey=60;
	if(NULL==myBinaryHeap.UpdateBinHeap(oldKey,newKey))
		cout<<"更新失败，没找到"<<oldKey<<endl;
	else cout<<"更新成功!"<<endl;
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;



	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;


	myBinaryHeap.DeleteMinElement();
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;



	newKey=55;
	if(myBinaryHeap.DeleteElement(newKey))
		cout<<newKey<<"删除成功!"<<endl;
	else cout<<newKey<<"删除失败!"<<endl;
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;


	newKey=50;
	if(myBinaryHeap.DeleteElement(newKey))
		cout<<newKey<<"删除成功!"<<endl;
	else cout<<newKey<<"删除失败!"<<endl;
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;


	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;
	myBinaryHeap.DeleteMinElement();
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;


	myBinaryHeap.DeleteMinElement();
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;

	myBinaryHeap.DeleteMinElement();
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;

	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;
	oldKey=ret->GetKey(),newKey=-100;
	if(NULL==myBinaryHeap.UpdateBinHeap(oldKey,newKey))
		cout<<"更新失败，没找到"<<oldKey<<endl;
	else cout<<"更新成功!"<<endl;
	ret=myBinaryHeap.GetMinElement();
	if(NULL==ret)
		cout<<"无元素!"<<endl;
	else cout<<"最小元素为"<<ret->GetKey()<<endl;


	system("pause");
	return 0;
}

