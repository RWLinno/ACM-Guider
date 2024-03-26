#include <bits/stdc++.h>
using ull=unsigned long long;
using namespace std;
const int N=1e6+7;
const ull base=131;
int n,q,len,cnt;
ull hs[N],pw[N];
int pri[N],np[N];
char s[N];

void init(){
    for(int i=2;i<N;i++){
        if(!np[i]) pri[++cnt]=i,np[i]=i;
        for(int j=1;j<=cnt&&i*pri[j]<N;j++){
            if(pri[j]>np[i]) break;
			np[pri[j]*i]=pri[j];
        }
    }
    pw[0]=1;
    for(int i=1;i<=n;i++)
        hs[i]=hs[i-1]*base+(ull)s[i],pw[i]=pw[i-1]*base;
}

bool valid(int a,int b,int l) {
    return hs[b]-hs[a+l-1]*pw[len-l]==hs[a+(len/l-1)*l-1]-hs[a-1]*pw[len-l];
}

signed main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    scanf("%d",&q);
    init();
    while(q--){
        int l,r,ans,tmp;
        scanf("%d%d",&l,&r);
        len=tmp=ans=r-l+1;
        while(tmp!=1){
            int t=np[tmp];
            while(tmp%t==0&&valid(l,r,ans/np[tmp])) tmp/=t,ans/=t;
            while(tmp%t==0) tmp/=t;
        }
        printf("%d\n",ans);
    }
    return 0;
}