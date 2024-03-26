#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N=1e6+7;
const int mod=1e9+7;

int n,len,nxt[N];
string str;

void kmp(){
	int j;
	for(int i=1;i<len;i++){
		j=nxt[i];
		while(j&&str[j]!=str[i]) j=nxt[j]; 
		nxt[i+1]=(str[j]==str[i])?j+1:0;
	}
}

signed main(){
	cin>>n;
	cin>>str;
	len=str.length();
	kmp();
	cout<<n-nxt[len]<<"\n";
	return 0;
}
