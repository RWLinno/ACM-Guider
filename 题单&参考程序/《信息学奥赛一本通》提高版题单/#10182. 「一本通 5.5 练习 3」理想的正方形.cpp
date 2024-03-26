#include<bits/stdc++.h>
using namespace std;
const int N = 1e4+7;
int a,b,n,head1,head2,tail1,tail2;
int s[N],q1[N],q2[N],mi[N][N],mx[N][N];

signed main() {
	scanf("%d%d%d",&a,&b,&n);
	for(int i=1;i<=a;++i){  //处理每一行上升和下降的单调队列 
		head1=head2=1;
		tail1=tail2=0;
		for(int j=1;j<=b;++j){
			scanf("%d",&s[j]);
			while(head1<=tail1&&q1[head1]<=j-n) ++head1;
			while(head2<=tail2&&q2[head2]<=j-n) ++head2;
			while (head1<=tail1&&s[j]>=s[q1[tail1]]) --tail1;
			while (head2<=tail2&&s[j]<=s[q2[tail2]]) --tail2;
			q1[++tail1]=j;
			q2[++tail2]=j;
			mx[i][j]=s[q1[head1]]; //记录(i,max(j-n+1,1))到(i,j)的最大最小值 
			mi[i][j]=s[q2[head2]];
		}
	}
	int ans=2e9;
	for(int j=n;j<=b;++j){ //对于每一列,找范围内最小的最大值和最大的最小值 
		head1=head2=1;
		tail1=tail2=0;
		for(int i=1;i<=a;++i){ //
			while(head1<=tail1&&q1[head1]<=i-n) ++head1;
			while(head2<=tail2&&q2[head2]<=i-n) ++head2;
			while(head1<=tail1&&mx[q1[tail1]][j]<=mx[i][j]) --tail1;
			while(head2<=tail2&&mi[q2[tail2]][j]>=mi[i][j]) --tail2;
			q1[++tail1]=i;
			q2[++tail2]=i;
			if(i>=n){
				ans=min(ans,mx[q1[head1]][j]-mi[q2[head2]][j]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}