#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int maxn=1007;
int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int fpow(int a,int b){
	int res=1;
	while(b){
		if(b&1) res=res*a;
		a=a*a;
		b>>=1;
	} 
	return res;
}

const int mod=fpow(2,31)-1;

int n,m,x,y,l;
int mp[maxn][maxn],f[maxn],dis[maxn],goal[maxn],vis[maxn];

bool cmp(int i,int j){
	return dis[i]<dis[j];
}

void spfa(int s){
	queue<int>q;
	q.push(s);
	memset(dis,inf,sizeof(dis));
	dis[s]=0;
	while(!q.empty()){
		int fro=q.front();
		q.pop();
		vis[fro]=0;
		for(int i=1;i<=n;i++){
			if(mp[fro][i]&&dis[i]>dis[fro]+mp[fro][i]){
				dis[i]=dis[fro]+mp[fro][i];
				if(!vis[i]){
					vis[i]=1;
					q.push(i);
				}
			}
		}
	}
} 

signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
//	freopen("in.cpp","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++) goal[i]=i;
	for(int i=1;i<=m;i++){
		cin>>x>>y>>l;
		mp[x][y]=mp[y][x]=l;
	}
	spfa(1);
	f[1]=1;
	int ans=1;
	sort(goal+1,goal+1+n,cmp);
	//for(int i=1;i<=n;i++) cout<<dis[goal[i]]<<" ";
	for(int i=1;i<=n;i++){ //前i个结点的方案数 
		for(int j=1;j<i;j++){ //枚举前面的节点 
			int x=goal[j],y=goal[i];
			if(mp[y][x]&&dis[y]==dis[x]+mp[y][x]){ //i可以从j转移过来
				f[y]++;
				f[y]%=mod; 
			//	cout<<y<<" "<<f[y]<<endl;
			}
		}
	}
	for(int i=1;i<=n;i++) ans*=f[i],ans%=mod;
	cout<<ans;
	return 0;
}
