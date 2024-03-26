#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;

int a[]={0,2,3,5,7,11,13,17,19,23,29};
int n,res,Ans;

void dfs(int num,int step,int lim,int ans){
	if(step>10) return;
	if(ans>Ans) Ans=ans,res=num;
	if(ans==Ans) res=min(res,num);
	int tmp=1;
	for(int i=1;i<=lim;i++){
		tmp*=a[step];
		if(tmp*num>n) return;
		dfs(num*tmp,step+1,i,ans*(i+1));
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	cin>>n;
	dfs(1,1,31,1);
	cout<<res<<endl;
	return 0;
}