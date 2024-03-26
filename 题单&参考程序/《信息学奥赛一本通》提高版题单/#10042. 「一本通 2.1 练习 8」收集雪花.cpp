#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;

struct hashmap{
	int head[N],nxt[N],tot,to[N],pos[N];
	void add(int w,int cur){
		int p=w%N;
		for(int i=head[p];i;i=nxt[i]){
			if(to[i]){
				pos[i]=cur;
				return;
			}
		}
		to[++tot]=w;
		pos[tot]=cur;
		nxt[tot]=head[p];
		head[p]=tot;
	}
	int query(int k){
		int p=k%N;
		for(int i=head[p];i;i=nxt[i]){
			if(to[i]==k) return pos[i];
		}
		return 0;
	}
}ha;

int n,ans,from=1;

signed main(){
	scanf("%d",&n);
	int now;
	for(int i=1;i<=n;++i){
		scanf("%d",&now);
		int lst=ha.query(now);
		if(lst>=from) from=lst+1;
		ans=max(ans,i-from+1);
		ha.add(now,i);
	}
	printf("%d",ans);
	return 0;
}