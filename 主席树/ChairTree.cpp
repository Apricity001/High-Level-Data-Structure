#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

/***************************************
*
*利用主席树求区间第k打元素
*
****************************************/
const int MAXN=100000+100;
const int MAXM=MAXN*20;

int tot,n,m;
int da[MAXN],sDa[MAXN];
int leftChild[MAXM],rightChild[MAXM],wei[MAXM],chairTNode[MAXM];

/**********************************
*参数：待处理元素区间
*功能：建立一棵空线段树
*返回值：返回根节点下标
***********************************/
int Build(int left,int right)
{
	int id=tot++;
	wei[id]=0;
	if(left<right)
	{
		int mid=(left+right)>>1;
		leftChild[id]=Build(left,mid);
		rightChild[id]=Build(mid+1,right);
	}
	return id;
}

/**********************************
*参数：前一棵线段树根节点，更新位置，更新后的值
*功能：利用历史版本更新原序列某个节点
*返回值：返回主席树节点即线段树根节点下标
***********************************/
int Update(int root,int pos,int val)
{
	int l=1,r=m,mid,newRoot=tot++,retRoot=newRoot;
	wei[newRoot]=wei[root]+val;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(pos<=mid)
		{
			//确定节点孩子节点
			leftChild[newRoot]=tot++;
			rightChild[newRoot]=rightChild[root];
			//确定待跟新节点以及历史版本
			newRoot=leftChild[newRoot];
			root=leftChild[root];
			r=mid;
		}
		else 
		{
			rightChild[newRoot]=tot++;
			leftChild[newRoot]=leftChild[root];
			newRoot=rightChild[newRoot];
			root=rightChild[root];
			l=mid+1;
		}
		wei[newRoot]=wei[root]+val;
	}
	return retRoot;
}

/**********************************
*参数：区间对应主席树节点下标，k
*功能：查询第k小元素
*返回值：返回第k小元素对应下标
***********************************/
int Query(int leftRoot,int rightRoot,int k)
{
	int  l=1,r=m,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(wei[leftChild[leftRoot]]-wei[leftChild[rightRoot]]>=k)//第k小值在左子树
		{
			//确定查找新区间
			leftRoot=leftChild[leftRoot];
			rightRoot=leftChild[rightRoot];
			r=mid;
		}
		else 
		{
			k-=wei[leftChild[leftRoot]]-wei[leftChild[rightRoot]];
			leftRoot=rightChild[leftRoot];
			rightRoot=rightChild[rightRoot];
			l=mid+1;
		}
	}
	return l;
}

int main()
{
	int q,i;
	int ql,qr,k;
	while(scanf("%d%d",&n,&q)!=EOF)
	{
		m=0;
		tot=0;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&da[i]);
			sDa[i]=da[i];
		}
		sort(sDa+1,sDa+n+1);
		m=unique(sDa+1,sDa+1+n)-sDa-1;
		chairTNode[n+1]=Build(1,m);
		for(i=n;i>=1;i--)
		{
			int pos=lower_bound(sDa+1,sDa+1+m,da[i])-sDa;
			chairTNode[i]=Update(chairTNode[i+1],pos,1);
		}
		while(q--)
		{
			scanf("%d%d%d",&ql,&qr,&k);
			printf("%d\n",sDa[Query(chairTNode[ql],chairTNode[qr+1],k)]);
		}
	}
	system("pause");
	return 0;
}
