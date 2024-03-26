#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
int t,L,R,len,num[25],pw[30];

struct P{
	ll s0,s1,s2;
	P(){s0=-1,s1=s2=0;}
	P(ll s0,ll s1,ll s2):s0(s0),s1(s1),s2(s2){}
}vis[25][10][10];

P dfs(int stp,int x,int k,bool lim,bool zero){
	//cout<<stp<<" "<<s<<" "<<x<<" "<<k<<" "<<lim<<" "<<zero<<"!!\n";
	if(!stp){
		if(x&&k) return P(1,0,0);
		return P(0,0,0);
	}
	if(!lim&&!zero&&vis[stp][x][k].s0!=-1) return vis[stp][x][k];
	P ans(0,0,0);
	int j=lim?num[stp]:9;
	for(int i=0;i<=j;++i){
		if(i==7) continue;
		P nxt=dfs(stp-1,(x*10+i)%7,(k+i)%7,lim&&(i==j),zero&&(i==0));
		ans.s0=(ans.s0+nxt.s0)%mod;
 		ans.s1=(ans.s1+nxt.s1+pw[stp]*i%mod*nxt.s0%mod)%mod;
 		ans.s2=(ans.s2+nxt.s2+2ll*pw[stp]*i%mod*nxt.s1%mod)%mod;
 		ans.s2=(ans.s2+(nxt.s0*pw[stp]%mod*pw[stp]%mod*i*i%mod))%mod;
	}
	if(!lim&&!zero) vis[stp][x][k]=ans;
	return ans;
}

ll solve(ll x){	
	len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	return dfs(len,0,0,1,1).s2;
}


signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>t;
	pw[1]=1;for(int i=2;i<30;++i) pw[i]=pw[i-1]*10%mod; 
	while(t--){
		cin>>L>>R;
		ll ans=(solve(R)-solve(L-1)+mod)%mod;
		cout<<ans<<"\n";
	}
	return 0;
} 