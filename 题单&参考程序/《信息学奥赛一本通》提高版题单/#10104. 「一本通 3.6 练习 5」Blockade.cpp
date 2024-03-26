//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

int n, m, rt, ans[N];

vector<int>G[N];
int dfn[N], low[N], idx = 0;
int vis[N], sz[N], is[N];

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    sz[x] = 1;
    int col = 0, sum = 0;

    for (auto to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            sz[x] += sz[to];
            low[x] = min(low[x], low[to]);

            if (low[to] >= dfn[x]) {
                ans[x] += sz[to] * sum;
                sum += sz[to];
            }
        } else
            low[x] = min(low[x], dfn[to]);
    }

    ans[x] += (n - sum - 1ll) * sum;
    ans[x] += n - 1;
}

void Solve() {
    cin >> n >> m;

    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            rt = i, tarjan(i);
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] * 2 << "\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;

    while (T--) {
        Solve();
    }

    return 0;
}