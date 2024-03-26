#include<bits/stdc++.h>
//#define mk make_pair
//#define pii pair<int,int> 
#define pii unsigned long long
#define mk(x,y) ((x)*1145157ll+(y))
using namespace std;
const int N=1e6+7;

int n,m,mx,stp;
char st[N],str[25][20];
int cnt[N],ed[N],tr[N][30],Len[N],idx;
bool dp[N];

void insert(char *ss,int id){
	int p=0,len=strlen(ss);
	++cnt[0];
	for(int i=0;i<len;++i){
		int c=ss[i]-'a';
		if(!tr[p][c]) tr[p][c]=++idx;
		p=tr[p][c];
		++cnt[p];
	}
	ed[p]=id;
}

signed main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%s",str[i]);
		insert(str[i],i);
	}
	for(int i=1;i<=m;++i){
		scanf("%s",st+1);
		stp=strlen(st+1);
		memset(dp,0,sizeof(dp));
		dp[0]=1;mx=0;
		for(int j=1;j<=stp;++j){
			if(dp[j-1]){
				int p=0;
				for(int k=j;k<=stp;++k){
					int c=st[k]-'a';
					if(!tr[p][c]) break;
					p=tr[p][c];
					if(ed[p]){
						mx=max(mx,k);
						dp[k]=1;
					}
				}
			}
		}
		printf("%d\n",mx);
	}
	return 0;
}