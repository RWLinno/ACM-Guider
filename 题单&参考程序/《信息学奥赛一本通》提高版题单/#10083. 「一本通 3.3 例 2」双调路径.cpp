#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
//俩个状态的SPFA+树状数组优化 
inline int mymin(int a,int b) {return a<b?a:b;}
inline int mymax(int a,int b) {return a>b?a:b;}
int n,m,s,e;
struct node
{
	int x,y,c,d,next;	//C->长度、D->时间 
}a[1100];int len,last[1100];
void ins(int x,int y,int c,int d)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;a[len].d=d;
	a[len].next=last[x];last[x]=len;
}
struct nnode
{
	int x,y;	//点、离起点路程 
}list[11000];int head,tail;
int f[110][11000],d[110][11000];//用f[i][j]表示到i点费用为j时的时间最短路
bool v[110][11000];	//判重 
int lowbit(int x) {return x & -x;}
void change(int x,int y,int k)
{
	y++;	//树状数组判断不了1，所以要+1 
    while(y<=n*100)
    {
        f[x][y]=mymin(f[x][y],k);
        y=y+lowbit(y);
    }
}
int getmin(int x,int y)
{
	y++;	//树状数组判断不了1，所以要+1 
    int ans=999999999;
    while(y>=1)
    {
        ans=mymin(ans,f[x][y]);
        y=y-lowbit(y);
    }
    return ans;
}
void spfa()
{
	memset(d,63,sizeof(d));d[s][0]=0;
	memset(f,63,sizeof(f));change(s,0,0);
	memset(v,false,sizeof(v));v[s][0]=true;
	head=1;tail=2;list[1].x=s;list[1].y=0;
	while(head!=tail)
	{
		nnode now=list[head];
		//下文s1、s2为路程 
		int x=now.x,s1=now.y;
		for(int k=last[x];k;k=a[k].next)
		{
			int y=a[k].y,s2=s1+a[k].c;
			if(d[x][s1]+a[k].d<getmin(y,s2))
			{
				d[y][s2]=d[x][s1]+a[k].d;
				change(y,s2,d[y][s2]);
				if(!v[y][s2])
				{
					v[y][s2]=true;
					list[tail].x=y;
					list[tail].y=s2;
					tail++;
					if(tail==10001) tail=1;
				}
			}
		}
		v[x][s1]=false;
		head++;
		if(head==10001) head=1;
	}
}
int main()
{
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for(int i=1;i<=m;i++)
	{
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		ins(a,b,c,d);	//建双向边 
		ins(b,a,c,d);
	}
	spfa();
	int ans=0,minn=999999999;
	for(int i=0;i<=n*100;i++)	//费用递增，时间递减 
	{
		if(d[e][i]<minn) {ans++;minn=d[e][i];}
	}
	printf("%d\n",ans);
	return 0;
}