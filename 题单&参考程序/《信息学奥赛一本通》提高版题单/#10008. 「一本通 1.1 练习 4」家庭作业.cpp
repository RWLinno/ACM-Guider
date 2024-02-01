#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 1e6 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X {
    int d, v;
    bool operator <(X b)const {
        return v < b.v;
    }
} s[N];

int n, mx, vis[N];

bool cmp(X a, X b) {
    return a.v > b.v;
}
bool cmp2(X a, X b) {
    return a.d > b.d;
}
priority_queue<X>q;


signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> s[i].d >> s[i].v;
        mx = max(mx, s[i].d);
    }

    sort(s + 1, s + 1 + n, cmp2);
    int idx = 1, ans = 0;

    for (int i = mx; i >= 1; i--) {
        while (idx > 0 && i <= s[idx].d)
            q.push(s[idx]), idx++;

        if (q.size()) {
            ans += q.top().v;
            q.pop();
        }
    }

    cout << ans << "\n";
    return 0;
}