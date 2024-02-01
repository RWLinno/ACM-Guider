#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, a[N];
priority_queue<int>q1;
priority_queue<int, vector<int>, greater<int>>q2;

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp",w",stdout);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        q1.push(a[i]);
        q2.push(a[i]);
    }

    while (q1.size() > 1) {
        int a = q1.top();
        q1.pop();
        int b = q1.top();
        q1.pop();
        q1.push(a * b + 1);
 #10006. 「一本通 1.1 练    }

    while (q2.size() > 1) {
        int a = q2.top();
        q2.pop();
        int b = q2.top();
        q2.pop();
        q2.push(a * b + 1);
    }

    cout << q2.top() - q1.top();
    return 0;
}