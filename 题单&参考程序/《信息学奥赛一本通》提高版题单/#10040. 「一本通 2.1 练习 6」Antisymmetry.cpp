#include <bits/stdc++.h>
#define ull unsigned long long
#define int long long
using namespace std;
const int N=1e6+7;
int n,len[N],ans=0;
char s[N],c[N];

signed main() {
    scanf("%d%s",&n,s+1);
    c[0]='$';
    for(int i=1;i<=n;i++){
        c[2*i-1]='#';
        c[2*i]=s[i];
    }
    c[2*n+1]='#';
	c[2*n+2]='$';
    int mx=0,po=0;
    for(int i=1;i<=2*n;i+=2){
        if(mx>i) len[i]=min(mx-i,len[2*po-i]);
        else len[i]=1;
        while((c[i+len[i]]==c[i-len[i]]&&c[i+len[i]]=='#')||(c[i+len[i]]-'0'+c[i-len[i]]-'0'==1)) len[i]++;
        if(i+len[i]>mx) mx=i+len[i],po=i;
        ans+=len[i]/2;
    }
    printf("%lld\n",ans);
    return 0;
}
