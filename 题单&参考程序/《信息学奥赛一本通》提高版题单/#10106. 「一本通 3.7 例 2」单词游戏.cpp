//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, st, ed, f1, f2, vis[N], mp[30][30], ru[30], chu[30], fa[30];
string str;

int find(int x) {
    if (fa[x] == x)
        return x;

    return find(fa[x]);
}

void Solve() {
    cin >> n;
    f1 = -1, f2 = 0;
    st = 0;
    ed = 0;
    memset(vis, 0, sizeof(vis));
    memset(mp, 0, sizeof(mp));
    memset(ru, 0, sizeof(ru));
    memset(chu, 0, sizeof(chu));

    for (int i = 0; i < 26; i++)
        fa[i] = i;

    for (int i = 1; i <= n; i++) {
        cin >> str;
        int u = str[0] - 'a', v = str[str.size() - 1] - 'a';
        mp[u][v] = 1;
        vis[u] = vis[v] = 1;
        chu[u]++;
        ru[v]++;
        fa[find(u)] = find(v);
    }

    for (int i = 0; i < 26; i++) {
        if (vis[i]) {
            if (f1 == -1)
                f1 = find(i);
            else if (f1 != find(i)) {
                f2 = 1;
                break;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (ru[i] != chu[i]) {
            if (chu[i] == ru[i] + 1)
                st++;
            else if (ru[i] == chu[i] + 1)
                ed++;
            else {
                f2 = 1;
                break;
            }
        }
    }

    if (st > 1 || ed > 1)
        f2 = 1;

    if (f2)
        cout << "The door cannot be opened.\n";
    else
        cout << "Ordering is possible.\n";
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;

    while (T--) {
        Solve();
    }

    return 0;
}