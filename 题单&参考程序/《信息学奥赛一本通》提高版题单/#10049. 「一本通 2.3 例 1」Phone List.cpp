#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7;

struct node{
	int ch[12],flag;
}tr[N<<5];

int t,n,cnt=0;
string S;

bool insert(string str,int id){
	int p=1,flag=0;
	int len=str.length();
	for(int i=0;i<len;i++){
		int v=str[i]-47;
		if(!tr[p].ch[v]) tr[p].ch[v]=++cnt;
		else if(i==len-1) flag=1; 
		p=tr[p].ch[v];
		if(tr[p].flag) flag=1; 
	}
	tr[p].flag=id;
	return flag;
}


signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		int flag=0;
		cnt=1;
		for(int i=1;i<=n;i++){
			cin>>S;
			flag|=insert(S,i);
		}
		if(flag) puts("NO");
		else puts("YES");
		for(int i=1;i<=cnt;i++){
			memset(tr[i].ch,0,sizeof(tr[i].ch));
			tr[i].flag=0;
		}		
	}
	return 0;
}