//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1005;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,mx,ans,tot[N],fa[N],in[N],out[N],fg[N];

inline int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

inline int merge(int x,int y){
	int fx=find(x),fy=find(y);
	return fa[fx]=fy;
}

void Solve(){
	cin>>n;
	ans=n;
	for(int i=1;i<=1000;++i) fa[i]=i;
	for(int i=1,u,v;i<=n;++i){
		cin>>u>>v;
		out[u]++;in[v]++;
		fg[u]=1;fg[v]=1;
		merge(u,v);
		mx=max(mx,max(u,v));
	}
	for(int i=1;i<=mx;++i) if(in[i]>out[i]){
		tot[find(i)]+=in[i]-out[i];
	}
	for(int i=1;i<=mx;++i){
		if(fg[i]&&find(i)==i){
			if(tot[i]==0) ++ans;
			else ans+=tot[i];
		}
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;
	return 0;
}