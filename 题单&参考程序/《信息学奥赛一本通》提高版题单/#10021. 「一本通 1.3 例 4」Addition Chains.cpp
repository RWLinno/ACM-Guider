#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, ans = inf, cnt = 0, lst[N];

inline void dfs(int mx, vector<int>v, int len) {
    if (len >= ans)
        return;

    if (mx == n) {
        cnt = 0;

        for (int i = 1; i <= n; i++)
            if (v[i])
                lst[++cnt] = i;

        ans = len;
        return;
    }

    for (int i = mx; i >= 1; i--) {
        if (v[i] == 1 && i + mx <= n) {
            v[mx + i] = 1;
            dfs(mx + i, v, len + 1);
            v[mx + i] = 0;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    while (n) {
        vector<int>vis(n + 1);
        vis[1] = 1;
        vis[n] = 1;
        ans = inf;
        dfs(1, vis, 2);

        for (int i = 1; i <= cnt; i++)
            cout << lst[i] << " ";

        cout << "\n";
        cin >> n;
    }

    return 0;
}