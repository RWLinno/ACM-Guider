//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, m;
int dfn[N], low[N], idx = 0;
int vis[N], stk[N], top = 0;
int bel[N], sccnum = 0;
vector<int>G[N];

inline void tarjan(int x) { //缩点
    dfn[x] = low[x] = ++idx;
    vis[x] = 1;
    stk[++top] = x;

    for (auto to : G[x]) {
        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        } else if (vis[to])
            low[x] = min(low[x], dfn[to]);
    }

    if (dfn[x] == low[x]) {
        int y;
        sccnum++;

        while (y = stk[top--]) {
            vis[y] = 0;
            bel[y] = sccnum;

            if (x == y)
                break;
        }
    }
}

bool check() {
    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i])
            tarjan(i);
    }

    for (int i = 1; i <= 2 * n; i += 2) {
        if (bel[i] == bel[i + 1])
            return 0;
    }

    return 1;
}

void Solve() {
    cin >> n >> m;

    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;

        if (u & 1)
            G[u + 1].push_back(v);
        else
            G[u - 1].push_back(v);

        if (v & 1)
            G[v + 1].push_back(u);
        else
            G[v - 1].push_back(u);
    }

    if (!check()) {
        cout << "NIE\n";
        return;
    } else {
        for (int i = 1; i <= 2 * n; i += 2) {
            if (bel[i] > bel[i + 1])
                cout << i << "\n";
            else
                cout << i + 1 << "\n";
        }
    }
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    int T = 1;

    //cin>>T;
    while (T--) {
        Solve();
    }

    return 0;
}