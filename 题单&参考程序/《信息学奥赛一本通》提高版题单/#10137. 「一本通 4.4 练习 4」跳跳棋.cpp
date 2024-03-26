#include<bits/stdc++.h>
using namespace std;
int read(){	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}
const int inf = 0x3f3f3f3f;

struct Node{
	int x,y,z;
	void Init(){
		x = read(),y = read(),z = read();
		if(x>y)swap(x,y); //记得维护顺序
		if(x>z)swap(x,z);
		if(y>z)swap(y,z);
	}
}a,b,ra,rb;

bool check(Node u,Node v){ //判断终极状态相同与否
	return u.x==v.x&&u.y==v.y&&u.z==v.z;
}

int step,k;

Node getroot(Node t,int s){ //转移到终极状态
	for(step=0;s;step+=k){
		int d1 = t.y-t.x,d2 = t.z-t.y;
		if(d1==d2) return t;
		if(d1<d2){
			k = min((d2-1)/d1,s); //跳多些
			t.x+=k*d1,t.y+=k*d1;
			s-=k;
		}
		else{
			k = min((d1-1)/d2,s);
			t.z-=k*d2,t.y-=k*d2;
			s-=k;
		}
	}
	return t;
}

signed main(){
	a.Init(),b.Init();
	ra = getroot(a,inf);
	int step1 = step;
	rb = getroot(b,inf);
	int step2=step;
	if(!check(ra,rb)){ //不同
		printf("NO\n");
		return 0;
	}
	if(step1<step2){ //一般求LCA的思想，先让远的先跳
		swap(a,b);
		swap(step1,step2);	
	}
	a=getroot(a,step1-step2);//跳到相同位置再一起跳
	int l=0,r=step2;
	while(l<r){
		int mid=(l+r)>>1; //枚举到祖先的距离，一起跳
		if(check(getroot(a,mid),getroot(b,mid))) r=mid;
		else  l=mid+1;
	}
	printf("YES\n%d\n",(l<<1)+step1-step2);//记得×2和加上a先跳的
}	