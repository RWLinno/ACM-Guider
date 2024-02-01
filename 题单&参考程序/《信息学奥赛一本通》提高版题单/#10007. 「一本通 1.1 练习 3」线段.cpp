#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 1e6 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X {
    int l, r;
} s[N];

bool cmp(X a, X b) {
    if (a.r == b.r)
        return a.l < b.l;

    return a.r < b.r;
}

int n;

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> s[i].l >> s[i].r;
    }

    sort(s + 1, s + 1 + n, cmp);
    int idx = 0, ans = 0;

    for (int i = 1; i <= n; i++) {
        if (s[i].l >= idx) {
            ans++;
            idx = s[i].r;
        }
    }

    cout << ans << "\n";
    return 0;
}