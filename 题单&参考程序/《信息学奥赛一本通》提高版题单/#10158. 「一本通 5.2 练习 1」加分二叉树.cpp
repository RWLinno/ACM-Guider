#include<bits/stdc++.h>
using namespace std;

int a[50],f[50][50],g[50][50];
//f[i][j]表示区间[i,j]最高加分 
//g[i][j]表示区间[i,j]的最优根节点 
void shuchu(int l,int r){ //输出该数的前序遍历 
	if(l>r) return;
	cout<<g[l][r]<<" ";
	shuchu(l,g[l][r]-1);
	shuchu(g[l][r]+1,r);
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);  
	}
	for(int len=1;len<=n;len++){ //枚举区间长度 
		for(int l=1;l+len-1<=n;l++){ //枚举区间起点 
			int r=l+len-1; 
			if(len==1){ //当区间为1时
				f[l][r]=a[l];//分数等于该节点的分数 
				g[l][r]=l; //根节点等于节点本身 
			}else{
				for(int k=l;k<=r;k++){ //对于区间[l,r]，以k为根节点划分左右 
					int left1,right1,fen;
					left1=(k==l)?1:f[l][k-1]; //左子树得分 
					right1=(k==r)?1:f[k+1][r]; //右子树得分 
					fen=left1*right1+a[k];  //记录分数 
					if(f[l][r]<fen){ //如果大于当前最佳答案 
						f[l][r]=fen;
						g[l][r]=k;
					}
				}
			}
		}
	}
	cout<<f[1][n]<<endl;
	shuchu(1,n);
	return 0;
}