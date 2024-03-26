#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 7;

int n, m, u, v, idx, ans;
int dfn[maxn], low[maxn], bel[maxn];
int vis[maxn], sz[maxn], deg[maxn];
int stk[maxn], top;
vector<int>G[maxn];

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    vis[x] = 1;
    stk[++top] = x;

    for (int i = 0; i < G[x].size(); i++) {
        int to = G[x][i];

        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to])
            low[x] = min(low[x], dfn[to]);
    }

    if (dfn[x] == low[x]) {
        int y;

        while (y = stk[top--]) {
            bel[y] = x;
            vis[y] = 0;
            if (x == y)
                break;
        }
    }
}


signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        bel[i] = i;

    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }

    for (int i = 1; i <= n; i++) {
        sz[bel[i]]++;

        /*
        if(sz[bel[i]]==n){ //形成了一个环
            cout<<n<<"\n";
            return 0;
        }
        */
        for (int j = 0; j < G[i].size(); j++) {
            if (bel[i] != bel[G[i][j]])
                deg[bel[i]]++; //记录出度
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!deg[bel[i]]) { //这个强连通分量没有出度
            if (ans && ans != bel[i]) { //存在多个
                cout << 0 << "\n";
                return 0;
            }

            ans = bel[i];
        }
    }

    cout << sz[ans] << "\n"; //答案就是唯一的强连通分量的大小
    return 0;
}