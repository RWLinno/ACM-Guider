#include<bits/stdc++.h>
using namespace std;
const int N=1<<10;

int n,m,mp[105],f[N][N][2],sum[N],ans=0; //f[i][j]表示前一行是状态i,后一行是状态j的答案，第三位用来滚动 
bool g[N];
char ch;

int getsum(int x){  //统计1的个数 
	int res=0;
	while(x){
		res+=(x&1);
		x>>=1;
	} 
	return res;
}

signed main(){
	cin>>n>>m;
	int M=(1<<m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			ch=getchar();
			while(ch!='P'&&ch!='H') ch=getchar();
			if(ch=='H') mp[i]=mp[i]<<1|1;
			else mp[i]=mp[i]<<1;
		} 
	}	
	for(int i=0;i<M;i++) sum[i]=getsum(i);  //预处理 
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){  //枚举前两行的状态和答案 
			if((i&j)||(i&mp[0])||(j&mp[1])||(i&(i<<1))||(j&(j<<1))||(i&(i<<2))||(j&(j<<2))) continue;
			f[i][j][1]=sum[i]+sum[j];
		}
	}
	for(int i=2;i<n;i++){  //枚举行 
		for(int j=0;j<M;j++){  //枚举第i-1行状态 
			if((j&mp[i-1])||(j&(j<<1))||(j&(j<<2))) continue;
			for(int k=0;k<M;k++){  //枚举第i行状态 
				if((k&(k<<1))||(k&(k<<2))||(k&mp[i])||(k&j)) continue;
				for(int v=0;v<M;v++){  //枚举第i-2行状态 
					if(v&(v<<1)||(v&(v<<2))||(v&j)||(v&k)||(v&mp[i-2])) continue;
					f[j][k][i%2]=max(f[j][k][i%2],f[v][j][(i-1)%2]+sum[k]);
				}
			}
		}
	}
	for(int i=0;i<M;i++){
		for(int j=0;j<M;j++){
			ans=max(ans,f[i][j][(n-1)%2]);  //取最大值 
		}
	}
	cout<<ans<<"\n";
	return 0;
}