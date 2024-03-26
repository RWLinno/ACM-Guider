//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define ull unsigned long long
#define base 233331 
using namespace std;
const int N=2e5+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
int n,res,mx,a[N],b[N];
ull pw[N],hs[N],hs2[N];
vector<int>ans;
map<ull,int>mp;

inline ull get_hs1(int l,int len){
	int r=l+len-1;
	return hs[r]-hs[l-1]*pw[len];
}

inline ull get_hs2(int l,int len){
	int r=l+len-1;
	return hs2[r]-hs2[l-1]*pw[len];
}

void Solve(){
	cin>>n;
	pw[0]=1;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		hs[i]=hs[i-1]*base+a[i];
		pw[i]=pw[i-1]*base;
	}
	for(int i=1;i<=n;++i){
		b[i]=n-i+1;
		hs2[i]=hs2[i-1]*base+a[b[i]];
	}
	for(int k=1;k<=n;++k){  //枚举段长 
		res=0;mp.clear();
		for(int j=1;j+k-1<=n;j+=k){ //枚举每一段hash 
			if(mp.count(get_hs1(j,k))) continue;
			mp[get_hs1(j,k)]=mp[get_hs2(b[j+k-1],k)]=1;
			++res;
		/*
			if(k==5){
			cout<<"nor: "<<j<<" "<<j+k-1<<" "<<get_hs1(j,k)<<"\n";
			cout<<"rev: "<<b[j+k-1]<<" "<<b[j+k-1]+k-1<<" "<<get_hs2(b[j+k-1],k)<<"\n";
				cout<<res<<"!!\n"; 
			}
		*/
		}
		if(res>mx){
			ans.clear();
			mx=res;
			ans.emplace_back(k);
		}else if(res==mx) ans.emplace_back(k);
	}
	cout<<mx<<" "<<ans.size()<<"\n";
	for(auto k:ans){
		cout<<k<<" ";
	}
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//  freopen("in.cpp","r",stdin);
//  freopen("out.cpp","w",stdout);
	int T=1;
//	cin>>T;
//	clock_t start,finish;
//	start=clock();
	while(T--){
		Solve();
	}
//	finish=clock();
//	cerr<<((double)finish-start)/CLOCKS_PER_SEC<<endl;	return 0;
}
