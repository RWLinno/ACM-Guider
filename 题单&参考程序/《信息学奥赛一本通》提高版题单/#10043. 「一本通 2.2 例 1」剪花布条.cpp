#include<bits/stdc++.h>
using namespace std;

string s1,s2;
int ans,j,nxt[100005];

signed main(){
	cin>>s1;
	while(s1!="#"){
		cin>>s2;
		ans=0,j=0;
		int len1=s1.size(),len2=s2.size();
		memset(nxt,0,sizeof(nxt));
		for(int i=1;i<len2;i++){
			j=nxt[i];
			while(j&&s2[i]!=s2[j]) j=nxt[j];
			nxt[i+1]=(s2[i]==s2[j])?j+1:0; 
		}
		//for(int i=0;i<=len2;i++) cout<<nxt[i]<<" ";
		j=0;
		for(int i=0;i<len1;i++){
			while(j&&s1[i]!=s2[j]) j=nxt[j]; 
			if(s1[i]==s2[j]){
				j++;
				if(j==len2) ans++,j=0;
			}
		}
		cout<<ans<<endl;
		cin>>s1;//下一次输入 
	}
	return 0;
}