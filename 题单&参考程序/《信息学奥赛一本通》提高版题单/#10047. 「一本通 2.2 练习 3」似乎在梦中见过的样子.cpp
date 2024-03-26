#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f

using namespace std;
const int N=1e5+7;
int n,k,nxt[N],mi[N],ans=0;
char str[N];

signed main(){
	scanf("%s%d",str+1,&k);
	n=strlen(str+1);
	for(int st=0;st<n;++st){
		nxt[0]=0,mi[0]=inf;
		for(int i=2,j=0;i<=n-st;++i){
			while(j&&str[st+i]!=str[st+j+1]) j=nxt[j];
			if(str[st+i]==str[st+j+1]) ++j;
			nxt[i]=j;mi[j]=j<k?inf:(j<mi[nxt[j]]?j:mi[nxt[j]]);
			if((mi[j]<<1)<i) ++ans;
		}
	}
	printf("%d\n",ans);
	return 0; 
} 