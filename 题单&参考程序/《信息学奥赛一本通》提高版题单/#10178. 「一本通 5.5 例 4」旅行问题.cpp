#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int n,p[N],d[N],a[N*2],f[N*2],b[N*2],g[N*2];
bool ans[N];
deque<int>q1,q2;

signed main(){
	cin>>n;
	for(int i=1; i<=n; i++) cin>>p[i]>>d[i];
	d[0]=d[n];
	for(int i=1;i<=n;i++){
		a[i+n]=a[i]=p[i]-d[i];
		b[i+n]=b[i]=p[n-i+1]-d[n-i];
	}
	for(int i=1;i<2*n;i++){  //顺时针和逆时针的前缀和 
		f[i]=f[i-1]+a[i];
		g[i]=g[i-1]+b[i];
	}
	for(int i=1;i<2*n;i++){
		while(q1.size()&&i-q1.front()>=n) q1.pop_front();
		while(q1.size()&&f[i]<=f[q1.back()]) q1.pop_back();
		q1.push_back(i);
		if(i>=n&&f[q1.front()]>=f[i-n]) ans[i-n+1]=1;
	}
	for(int i=1;i<2*n;i++){
		while(q2.size()&&i-q2.front()>=n) q2.pop_front();
		while(q2.size()&&g[i]<=g[q2.back()]) q2.pop_back();
		q2.push_back(i);
		if(i>=n&&g[q2.front()]>=g[i-n]) ans[2*n-i]=1;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]) puts("TAK");
		else puts("NIE");
	}
	return 0;
}