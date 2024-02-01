//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 55;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct E {
    int f, v, w, nxt;
} e[10086];
int head[N], cnt = 0;
inline void addedge(int f, int v, int w) {
    e[++cnt] = (E) {
        f, v, w, head[f]
    };
    head[f] = cnt;
    e[++cnt] = (E) {
        v, f, w, head[v]
    };
    head[v] = cnt;
}

int n, x[N], y[N], fa[N], t[N][N];

bool cmp(E a, E b) {
    return a.w < b.w;
}

int find(int x) {
    if (fa[x] == x)
        return x;

    return fa[x] = find(fa[x]);
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= n; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            addedge(i, j, (abs(x[i] - x[j]) + abs(y[i] - y[j]) + 1) / 2); //建边
        }
    }

    sort(e + 1, e + 1 + cnt, cmp);
    int num = 0, mx = 0;

    for (int i = 1; i <= cnt; i++) {
        int u = find(e[i].f), v = find(e[i].v);

        if (u == v)
            continue;

        fa[u] = v;
        mx = max(mx, e[i].w);
        num++;

        if (num >= n - 1)
            break;
    }

    cout << mx << "\n";
    return 0;
}