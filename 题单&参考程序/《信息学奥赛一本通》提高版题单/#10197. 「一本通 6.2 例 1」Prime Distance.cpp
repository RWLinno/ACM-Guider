#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N=1e6+7;
const int mod=1e9+7;

//int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
int L,R; 
int cnt=0,pri[N],is_pri[N];
void get_prime(){
	memset(is_pri,1,sizeof(is_pri));
	is_pri[1]=0;
	for(int i=2;i<=1000000;i++){
		if(is_pri[i]) pri[++cnt]=i;
		for(int j=1;j<=cnt&&i*pri[j]<=1000000;j++){
			is_pri[i*pri[j]]=0;
			if(i%pri[j]==0) break;
		}
	}
}

signed main(){
	get_prime();
	while(cin>>L>>R){
		int tmp,flag,sml=0,big=0,lf=0,rg=0,lst=0,mx=inf,mi=0;
		for(int i=L;i<=R;i++){
			tmp=sqrt(R),flag=0;
			if(i<=1000000){
				if(!is_pri[i]) flag=1;
			}
			else for(int j=1;j<=cnt;j++){
				if(pri[j]>tmp) break;
				if(i%pri[j]==0){flag=1;break;}
			}
			if(!flag){
				if(!lst){lst=i;continue;}
				if(i-lst<mx) mx=i-lst,lf=lst,rg=i;
				if(i-lst>mi) mi=i-lst,sml=lst,big=i;
				lst=i;
			}
		}
		if(mx==inf) cout<<"There are no adjacent primes.\n";
		else cout<<lf<<","<<rg<<" are closest, "<<sml<<","<<big<<" are most distant.\n"; 
	}
	return 0;
}