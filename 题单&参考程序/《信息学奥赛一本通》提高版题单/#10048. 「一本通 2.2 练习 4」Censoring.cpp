#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int stk[N],top=0,nxt[N],fj[N];
char S[N],T[N];

signed main(){
	scanf("%s%s",S+1,T+1); 
	int lens=strlen(S+1),lent=strlen(T+1);
	nxt[0]=0;
	for(int i=2,j=0;i<=lent;++i){
		while(j&&T[j+1]!=T[i]) j=nxt[j];
		if(T[i]==T[j+1]) ++j;
		nxt[i]=j; 
	}
	for(int i=1,j=0;i<=lens;++i){
		while(j&&S[i]!=T[j+1]) j=nxt[j];
		if(S[i]==T[j+1]) ++j;
		stk[++top]=i;
		fj[i]=j;
		if(j==lent){
			top-=lent;
			j=fj[stk[top]];
		}
	}
	for(int i=1;i<=top;++i) cout<<S[stk[i]];
	return 0;
} 