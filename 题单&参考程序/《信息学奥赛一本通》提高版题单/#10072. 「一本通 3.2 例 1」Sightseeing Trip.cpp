#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=107;

int n,m,ans=inf;
int mp[N][N],dis[N][N]; //邻接矩阵和最短路 
int pos[N][N];  //记录中转点 
int path[N],cnt=0; //答案路径 
inline void getpath(int i,int j){  //插入i到j的中间点 
    if(!pos[i][j]) return;
    int k=pos[i][j];
    getpath(i,k); 
    path[cnt++]=k;
    getpath(k,j);
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
  	cin>>n>>m;
  	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) mp[i][j]=inf;
		mp[i][i]=0;  
	}
    for(int i=1,u,v,w;i<=m;i++){
        cin>>u>>v>>w;
        mp[u][v]=mp[v][u]=min(mp[u][v],w);
    }
    memcpy(dis,mp,sizeof(mp));
    for(int k=1;k<=n;k++){  //枚举中间点 
        for(int i=1;i<k;i++){
            for(int j=i+1;j<k;j++){
                if(dis[i][j]+mp[i][k]+mp[k][j]<ans){ //不经过k时i到j的最短路 
                    ans=dis[i][j]+mp[i][k]+mp[k][j];
                    cnt=0;
                    path[cnt++]=k;
                    path[cnt++]=i;
                    getpath(i,j);
                    path[cnt++]=j;
                }
            }
        }
        for(int i=1;i<=n;i++){ //正常的floyd,更新最短路和中转点 
            for(int j=1;j<=n;j++){
                if(dis[i][j]>dis[i][k]+dis[k][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                    pos[i][j]=k;
                }
            }
        }
    }
    if(ans>=inf) printf("No solution.\n");
    else for(int i=0;i<cnt;i++) printf("%lld ",path[i]);
    return 0;
}
