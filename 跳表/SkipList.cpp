#include<iostream>
#include<ctime>
using namespace std;

const int MAXN_LEVEL=10;

struct SNode
{
	int key;
	SNode *forword[MAXN_LEVEL];
};

struct SkipList
{
	int nowLevel; 
	SNode *head;
};



/************************************************
*参数：myList为指向跳表头结点的指针
*功能:初始化跳表
*************************************************/
void InitSkipList(SkipList *& myList)
{
	 myList=new SkipList;
	 myList->nowLevel=0;
	 myList->head=new SNode;
	 for(int i=0;i<MAXN_LEVEL;i++)
		 myList->head->forword[i]=NULL;
}

/************************************************
*参数：myList为指向跳表头结点的指针，x为待插入元素，countRet为查找次数
*功能:在跳表中插入元素x
*************************************************/
bool InsertSkipList(SkipList *myList,int val)
{
	if(NULL==myList)
		return false;
	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	SNode *upDateNode[MAXN_LEVEL];
	while(k>=0)
	{
		q=p->forword[k];
		while(NULL!=q&&q->key<val)
		{
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
		     return false;
		upDateNode[k]=p;
		--k;
	}
	k=rand()%(MAXN_LEVEL-1);
	if(k>myList->nowLevel)
	{
		k=++myList->nowLevel;
		upDateNode[k]=myList->head;
	}
	p=new SNode;
	p->key=val;
	for(int i=0;i<=k;i++)
	{
		q=upDateNode[i];//q指向前面小于x的
		p->forword[i]=q->forword[i];
		q->forword[i]=p;
	}
	//for(int i=k+1;i<=myList->nowLevel;i++)
	 for(int i=k+1;i<MAXN_LEVEL;i++)
	        p->forword[i]=NULL;
	return true;
}

/************************************************
*参数：myList为指向跳表头结点的指针，x为待查找元素，countRet为查找次数
*功能:查找跳表中是否存在元素x
*************************************************/
SNode* FindSkipList(SkipList * myList,int val,int &countRet)
{
	if(NULL==myList)
		return NULL;

	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	while(k>=0)
	{
		q=p->forword[k];
		++countRet;
		while(NULL!=q&&q->key<val)
		{
			++countRet;
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
		    return q;
		--k;
	}
	return NULL;
}

/************************************************
*参数：myList为指向跳表头结点的指针，x为待删除元素
*功能:删除跳表中元素x
*************************************************/
bool DeleteSkipList(SkipList * myList,int val)
{
	int tmpCountRet=0;
	SNode *ret=FindSkipList(myList,val,tmpCountRet);
	if(NULL==ret)
		return false;

	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	SNode *upDateNode[MAXN_LEVEL];

	 for(int i=0;i<MAXN_LEVEL;i++)
		upDateNode[i]=NULL;
	
	while(k>=0)
	{
		q=p->forword[k];
		while(NULL!=q&&q->key<val)
		{
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
			 upDateNode[k]=p;
		--k;
	}

	for(int i=0;i<=myList->nowLevel;i++)
	{
		q=upDateNode[i];//q指向前面小于x
		if(NULL!=q&&q->forword[i]==ret)
			q->forword[i]=ret->forword[i];
	}
	delete ret;
	return true;
}



int main()
{
	int val;
	SkipList *  myList;
	InitSkipList(myList);

	while(cin>>val)
	{
		if(!InsertSkipList(myList,val))
			cout<<val<<"插入失败!"<<endl;
		else cout<<val<<"插入成功!"<<endl;
		/*
		int countRet=0;
		if(NULL!=FindSkipList(myList,val,countRet))
			cout<<val<<"查找成功!"<<endl;
		else cout<<val<<"查找失败!"<<endl;
		cout<<"共查找了"<<countRet<<"次"<<endl;
		*/
		/*
		DeleteSkipList(myList,val);
		countRet=0;
		if(NULL!=FindSkipList(myList,val,countRet))
			cout<<val<<"查找成功!"<<endl;
		else cout<<val<<"查找失败!"<<endl;
		cout<<"共查找了"<<countRet<<"次"<<endl;
		*/

	}
	system("Pause");
}

