#include<bits/stdc++.h>
using namespace std;
const int N=4e5+7;
typedef long long ll;

int tr[N<<5][2],tot=0;
int n,a[N],lsum[N],rsum[N],lans[N],rans[N];


void insert(int x){
	int p=0;
	for(int i=30;i>=0;--i){
		int c=(x>>i)&1;
		if(!tr[p][c]) tr[p][c]=++tot;
		p=tr[p][c];
	}
}

int getans(int x){
	int p=0,ans=0;
	for(int i=30;i>=0;--i){
		int c=(x>>i)&1;
		if(tr[p][c^1]==0) ans<<=1,p=tr[p][c];
		else ans=(ans<<1|1),p=tr[p][c^1]; 
	}
	return ans;
}

void init(){
	memset(tr,0,sizeof(tr));
	tot=0;
}

signed main(){
	scanf("%d",&n);
	tot=0;
	lsum[0]=0;lans[n+1]=0;
	rsum[n+1]=0;rans[0]=0;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=1;i<=n;++i) lsum[i]=lsum[i-1]^a[i];
	for(int i=n;i>=1;--i) rsum[i]=rsum[i+1]^a[i];
	init();
	for(int i=n;i>=0;--i){
		lans[i]=max(getans(lsum[i]),lans[i+1]);
		insert(lsum[i]);
	}
	init();
	for(int i=1;i<=n+1;++i){
		rans[i]=max(getans(rsum[i]),rans[i-1]);
		insert(rsum[i]);
	}
	ll ans=0;
	for(int i=0;i<=n;++i){
		ans=max(ans,(ll)lans[i]+rans[i+1]);
	}
	printf("%lld\n",ans);
	return 0;
} 