#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdio>
#include<cmath>
#define rep(i,x,y) for(int i=x; i<=y; ++i)

using namespace std;
const int N=505;
int n,m,k,fa[N];
struct point{int x,y;} p[N];
struct edge{int x,y,w;} edg[N*N];

int getfa(int x)
{
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}

void merge(int x,int y)
{
	x=getfa(x),y=getfa(y);
	if(x!=y) fa[x]=y,--n;
}

int sqr(int x)
{
	return x*x;
}

bool cmp(edge a,edge b)
{
	return a.w<b.w;
}

int main()
{
	scanf("%d%d",&n,&k);
	rep(i,1,n) fa[i]=i;
	rep(i,1,n) scanf("%d%d",&p[i].x,&p[i].y);
	rep(i,1,n) rep(j,i+1,n) edg[++m]=(edge){i,j,sqr(p[i].x-p[j].x)+sqr(p[i].y-p[j].y)};
	sort(edg+1,edg+1+m,cmp);
	if(k>=n) return puts("0.00"),0;
	rep(i,1,m)
	{
		merge(edg[i].x,edg[i].y);
		if(n<=k) return printf("%.2lf\n",sqrt(edg[i].w));
	}
	return 0;
}