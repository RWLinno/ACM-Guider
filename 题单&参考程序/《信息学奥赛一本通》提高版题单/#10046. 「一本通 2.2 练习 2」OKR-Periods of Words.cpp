//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int len,ans=0,nxt[N],f[N];
string str;

void getnxt(){
	int j=0;
	nxt[0]=0;
	for(int i=1;i<len;i++){
		j=nxt[i];
		while(j&&str[i]!=str[j]) j=nxt[j];
		nxt[i+1]=(str[i]==str[j])?j+1:0;
	}
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>len;
	cin>>str;
	getnxt();
	for(int i=1;i<=len;i++){
		f[i]=(nxt[i])?f[nxt[i]]:i;
		ans+=i-f[i];
	}
	cout<<ans;
	return 0;
}
