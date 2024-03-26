#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 7;

struct E {
    int u, v, nxt;
} e[N << 2];
int head[N], cnt = 1;
inline void addedge(int u, int v) {
    e[++cnt] = (E) {
        u, v, head[u]
    };
    head[u] = cnt;
}

int n, m, mx = 0, root, bl = 0;
int dfn[N], low[N], idx = 0;

void tarjan(int x, int w) {
    dfn[x] = low[x] = ++idx;
    int col = 0;

    for (int i = head[x]; i; i = e[i].nxt) {
        if (w == (i ^ 1))
            continue;

        int to = e[i].v;

        if (!dfn[to]) {
            tarjan(to, i);
            low[x] = min(low[x], low[to]);

            if (low[to] >= dfn[x])
                col++;
        } else
            low[x] = min(low[x], dfn[to]);
    }

    if (root != x)
        col++;

    mx = max(mx, col);
}

void Solve() {
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        u++;
        v++;
        addedge(u, v);
        addedge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            bl++, root = i, tarjan(i, 0); //块个数++，缩点
    }

    cout << bl + mx - 1 << "\n";
}

void clear() {
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(head, 0, sizeof(head));
    mx = 0;
    bl = 0;
    idx = 0;
    cnt = 1;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    while (n || m) {
        Solve();
        clear();
        cin >> n >> m;
    }

    return 0;
}