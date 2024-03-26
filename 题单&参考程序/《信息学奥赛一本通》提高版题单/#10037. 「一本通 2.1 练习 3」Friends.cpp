#include<bits/stdc++.h>
const int N=2e6+7;
using namespace std;

int main(){
	int n,m;
	string u,s1,s2;
	int f1=0,f2=0;
	cin>>n;
	cin>>u;
	if(n%2==0){
		cout<<"NOT POSSIBLE\n";
		return 0;
	}
	m=n/2;
	s1=u.substr(0,m);
	int j=0;
	for(int i=m;i<n&&j<m;i++) if(u[i]==s1[j]) j++;
	if(m==j) f1=1;
	s2=u.substr(n-m,m);
	j=0;
	for(int i=0;i<n-m && j<m;i++) if(u[i]==s2[j]) j++;
	if(m==j) f2=1;
	if(f1==0&&f2==0) cout<<"NOT POSSIBLE";
	else if(f1==1&&f2==1&&s1!=s2) cout<<"NOT UNIQUE";
	else if(f1==1) cout<<s1<<endl;
	else cout<<s2<<endl;
	return 0;
}