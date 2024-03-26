#include<bits/stdc++.h>
#define debug(x) cout<<"x="<<x<<endl
#define int long long
using namespace std;
const int maxn=305;
const int mod=1e9+7;
/*
inline void read(int &data){
	int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	data=x*f;
}
*/
	
struct X{
	int id,val;
}s[maxn];
	
struct E{
	int from,to,dis,nxt;
}e[maxn*maxn];

int cnt=0,head[maxn],num=0,ans=0;
int n,fa[maxn],mp[maxn][maxn];
vector<int>vt;

void addedge(int from,int to,int dis){
	e[++cnt].nxt=head[from];
	e[cnt].from=from;
	e[cnt].to=to;
	e[cnt].dis=dis;
	head[from]=cnt;
}

bool cmp(E a,E b){return a.dis<b.dis;}
bool cmp2(X a,X b){
	if(a.val==b.val) return a.id<b.id;
	return a.val<b.val;
}

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

void unite(int x,int y){
	fa[find(x)]=find(y); 
}

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//	freopen("in.cpp","r",stdin);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i].val;
		s[i].id=i;
		addedge(0,i,s[i].val);
	}//一开始全部建发电站 
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>mp[i][j];
			if(i!=j) addedge(i,j,mp[i][j]);
		}
	}
	sort(e+1,e+1+cnt,cmp);
	sort(s+1,s+1+n,cmp2);
	for(int i=1;i<=cnt;i++){
		int u=e[i].from,v=e[i].to; 
		if(find(u)!=find(v)){
			unite(u,v);
			ans+=e[i].dis;
		}
	}
	cout<<ans<<"\n";
	return 0;
}


