//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 30005;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
struct E {
    int v, nxt;
} e[N << 1];
int head[N], cnt = 1;
inline void addedge(int u, int v) {
    e[++cnt] = (E) {
        v, head[u]
    };
    head[u] = cnt;
}

int n, m, ans;
int dfn[N], low[N], idx = 0;
int vis[N << 1], is[N], root;
void tarjan(int x) {
    dfn[x] = low[x] = ++idx;

    for (int i = head[x]; i; i = e[i].nxt) {
        if (vis[i / 2] == 1)
            continue;

        vis[i / 2] = 1; //表示这条边有无走过
        int to = e[i].v;

        if (!dfn[to]) {
            tarjan(to);
            low[x] = min(low[x], low[to]);

            if (dfn[x] < low[to]) { //如果不经过这条边就不能到达u之前的点，那么这条边就是桥
                is[i / 2] = 1;
            }
        } else
            low[x] = min(low[x], dfn[to]);
    }
}

void Solve() {
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            root = i, tarjan(i);

    for (int i = 1; i <= m; i++)
        if (is[i])
            ans++;

    cout << ans << "\n";
}

void clear() {
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(vis, 0, sizeof(vis));
    memset(is, 0, sizeof(is));
    memset(head, 0, sizeof(head));
    idx = 0;
    cnt = 1;
    ans = 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> n >> m;

    while (n || m) {
        for (int i = 1, u, v; i <= m; i++) {
            cin >> u >> v;
            addedge(u, v);
            addedge(v, u);
        }

        Solve();
        cin >> n >> m;
        clear();
    }

    return 0;
}