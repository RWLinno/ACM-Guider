//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define lb(x) (x&-x) 
using namespace std;
const int N=1e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int n,k,tr[N],m,p;
char op;

void upd(int x,int p){for(;x<=n;x+=lb(x)) tr[x]+=p;}

int ask(int x){int res=0;for(;x;x-=lb(x)) res+=tr[x];return res;}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=k;i++){
		cin>>op>>m;
		if(op=='A'){
			cout<<ask(m)<<"\n";
		}else if(op=='B'){
			cin>>p;
			upd(m,p);
		}else if(op=='C'){
			cin>>p;
			upd(m,-p);
		}
	}
	return 0;
}