#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int maxn=1e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n,nxt[maxn],j;
string str;

void get_nxt(){
	nxt[0]=0;
	for(int i=1;i<n;i++){
		j=nxt[i];
		while(j&&str[i]!=str[j]) j=nxt[j];
		nxt[i+1]=(str[j]==str[i])?j+1:0;
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	cin>>str;
	while(str!="."){
		n=str.size();
		get_nxt();
		if(n%(n-nxt[n])==0) printf("%d\n",n/(n-nxt[n]));
		else printf("1\n");
		cin>>str;
	}
	return 0;
}
