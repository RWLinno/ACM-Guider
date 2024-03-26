//并查集 
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m;
int fa[N],deg[N],line[N],op[N];
int kcnt,cnt,ans;

int find(int x) {
	if (x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

void merge(int x, int y){
	fa[find(x)]=find(y);
}

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i] = i;
	for (int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
		if(!u){  //如果没有连任何点，与另一端相连 
			u=++n;
			fa[u]=u;
		}
		if(!v){
			v=++n;
			fa[v]=v;
		}
		deg[u]++; deg[v]++;
		merge(u,v);  //将两端合并 
	}
	for (int i=1;i<=n;i++) {
		if (fa[i]==i&&deg[i]){  //有连接的集合数 
			kcnt++;
		}
	}
	for(int i=1;i<=n;i++){
		if(deg[i]&1){
			cnt++;
			line[find(i)]=1;
		}
		if(deg[i]>2){
			ans++;
			op[find(i)]=1;
		}
	}
	if(kcnt>1){
		for(int i=1;i<=n;i++) {
			if(fa[i]==i&&deg[i]&&!line[i]){
				ans++;
				if(!op[i]) ans++;
			}
		}
	}
	printf("%d\n",ans+cnt/2);
	return 0;
}