#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 107, M = 1007;
const int mod = 31011;

struct e {
	int x, y, v;
} tp[M], mst[M]; //存放原图和最小生成树,边权离散化并按相等边权存储

vector<e>edge[M];

int cmp(e a, e b) { //权值较小的边靠前
	return a.v < b.v;
}

bool is[M];
int fa[N], bel[N];

int find(int x) { //并查集的查找操作
	if (fa[x] == x) {
		return x;
	}

	return fa[x] = find(fa[x]);
}

bool unite(int a, int b) { //并查集的合并操作
	int p = find(a), q = find(b);

	if (p == q) {
		return true;
	}

	fa[p] = q;
	return false;
}

int n, deg[N][N], g[N][N], mat[N][N];//度数矩阵、邻接矩阵、基尔霍夫矩阵

int treecnt(){ //生成树计数->矩阵树定理->高斯消元
	int i,j,k,ans=1;
	for(int i=1;i<n;i++){ //列举每一列
		for(int j=i+1;j<n;j++){ //对于对角线下方所有元素
			while(mat[j][i]){ //如果不为0
				int div=mat[i][i]/mat[j][i];
				for(int k=i;k<n;k++){
					mat[i][k]=(mat[i][k]-1ll*mat[j][k]*div%mod+mod)%mod;
				}
				//化0处理，并改变当前行其他元素的值
				swap(mat[i],mat[j]);
				ans*=-1; //交换两行，行列式符号改变
			}
			if(mat[i][i]==0){
				return 0;    //对角线有元素为0，结果必然是0
			}
		}
		ans=1ll*ans*mat[i][i]%mod; //对角线元素相乘
	}
	return (ans+mod)%mod; //防止负数
}

signed main() {
	int a,b,tl=0,tmp=0,cnt=0;
	cin>>a>>b;
	for (int i=1;i<=a;i++) fa[i]=i;
	for (int i=0;i<b;i++){
		cin>>tp[i].x>>tp[i].y>>tp[i].v;
	}
	sort(tp,tp+b,cmp); //边排序
	for (int i=0;i<b;i++){ //kruskal构建最小生成树
		if(tp[i].v!=tmp) tl++,tmp=tp[i].v;    //记录下多条权值相同边
		edge[tl].push_back(tp[i]); //加边
		if(unite(tp[i].x,tp[i].y))	continue;    //如果已经在同一集合中了，跳过
		is[tl]=1,mst[cnt]=tp[i],mst[cnt++].v=tl;
		//is表示该边可用
	}
	if(cnt!=a-1) { //表示没有最小生成树
		printf("0");
		return 0;
	}
	int ans=1;
	for(int i=1;i<=tl;i++){
		if(!is[i]) continue;    //如果最小生成树中没有用到过此边权
		for (int j=1;j<=a;j++) fa[j]=j;    //初始化集合
		int sz=edge[i].size();
		n=0; //将生成树上的边全部连上并缩点
		for(int j=0;j<cnt;j++){
			if (mst[j].v==i) 	continue;  //非自环 
			unite(mst[j].x,mst[j].y); //合并j边的两个端点
		}
		for(int j=1;j<=a;j++){
			if(fa[j]==j){
				bel[j]=++n; //表示缩成了n个点
			}
		}
		for(int j=1;j<=a;j++){
			bel[j]=bel[find(j)]; //缩点操作
		}
		for (int j=0;j<sz;j++) { //将原图中此边权的边全部连上
			int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
			deg[bx][bx]++, deg[by][by]++; //度数矩阵改变
			g[bx][by]++, g[by][bx]++; //邻接矩阵改变
		}
		for(int j=1;j<=n;j++){
			for(int k=1;k<=n;k++){
				mat[j][k]=deg[j][k]-g[j][k]; //构造基尔霍夫矩阵
			}
		}
		ans=ans*treecnt()%mod; //统计答案
		for(int j=0;j<sz;j++) { //删除连上的边
			int bx=bel[edge[i][j].x],by=bel[edge[i][j].y];
			deg[bx][bx]--,deg[by][by]--; //度数矩阵改变
			g[bx][by]--,g[by][bx]--; //邻接矩阵改变
		}
	}
	printf("%d", ans); //输出答案
	return 0;
}