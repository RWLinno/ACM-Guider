#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

int n,m,a[N],st[N];
int lg[N],f[N][25];
map<int,int>pr;

void init(){  //初始化对数 
	lg[1]=0;
	for(int i=2;i<N;i++) lg[i]=lg[i/2]+1;
}

void GM(){ 
	for(int j=1;j<=22;j++){ 
		for(int i=1;i+(1<<j)-1<=n;i++){
			f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]); //记录i到i+2^j的最大f[j] 
		}
	}
}

int Getmax(int x,int y){
	int s=lg[y-x+1],ans=max(f[x][s],f[y-(1<<s)+1][s]); 
	return ans;
}

int Solve(int l,int r){ //找到st[x]>=L的位置，前面的答案取x-L,后面的答案RMQ 
	if(st[l]==l) return l;
	if(st[r]<=l) return r+1;
	int L=l,R=r;
	while(l<r){
		int mid=(l+r)>>1;
		if(st[mid]>=L) r=mid;
		else l=mid+1;
	}
	return l;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		st[i]=max(st[i-1],pr[a[i]]+1); //记录以i结尾的最长完美序列起点 
		pr[a[i]]=i;  //记录上一个a[i]的位置 
		f[i][0]=i-st[i]+1; //以i结尾的最长完美序列长度 
	}
	init();
	GM();
	for(int i=1,l,r;i<=m;i++){
		cin>>l>>r;
		l++;r++;
		int L=l,R=r,ans=0;
		l=Solve(L,R);
		if(l>L) ans=l-L;
		if(l<=R) ans=max(ans,Getmax(l,R)); //这一部分保证了st[i]>=l 
		cout<<ans<<"\n";
	}
	return 0;
}