#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct node{
	int ch[2],flag;
}tr[N<<5];

int cnt,n,ans,s[N];

void insert(int num,int id){
	int p=1,v;
	for(int i=30;i>=0;i--){
		v=(num>>i)&1;
		if(!tr[p].ch[v]) tr[p].ch[v]=++cnt;
		p=tr[p].ch[v];
	}
	tr[p].flag=id;
}

int query(int num){
	int p=1,res=0,v;
	for(int i=30;i>=0;i--){
		v=(num>>i)&1;
		if(!tr[p].ch[v^1]) p=tr[p].ch[v];
		else p=tr[p].ch[v^1],res|=(1<<i);
	}
	return res;
}

signed main(){
//	ios::sync_with_stdio(0);//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);freopen("out.cpp","w",stout);
	cin>>n;
	cnt=1,ans=0;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		insert(s[i],i);
		ans=max(ans,query(s[i]));
	}
	cout<<ans<<"\n";
	return 0;
}
