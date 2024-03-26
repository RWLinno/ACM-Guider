//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define base 101
#define int unsigned long long
using namespace std;
const int N=6e5+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

string str;
int len,pw[N],hs[N];

inline void get_hash(string s){
	hs[0]=0;
	for(int i=1;i<=len;i++){
		hs[i]=(hs[i-1]*base+s[i-1]-'A');
	}
}

inline int get_hash(int i,int l){
	return (hs[i+l-1]-hs[i-1]*pw[l]);
} 

void init(){
	pw[0]=1;
	for(int i=1;i<=400000;i++){
		pw[i]=pw[i-1]*base;
	}
}

signed main(){
	init();
	while(cin>>str){
		memset(hs,0,sizeof(hs));
		len=str.length();
		get_hash(str);
		for(int l=1;l<=len;l++){
			if(get_hash(1,l)==get_hash(len-l+1,l)) cout<<l<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
