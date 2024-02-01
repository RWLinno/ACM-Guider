#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int maxn = 505;

struct X {
    int t, f;
} s[maxn];

bool cmp(X a, X b) {
    return a.f > b.f;
}

int n, m, ans = 0, vis[maxn];

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> m >> n;

    for (int i = 1; i <= n; i++)
        cin >> s[i].t;

    for (int i = 1; i <= n; i++)
        cin >> s[i].f;

    sort(s + 1, s + 1 + n, cmp);

    for (int i = 1; i <= n; i++) {
        int tmp = s[i].t;

        while (vis[tmp] && tmp)
            tmp--;

        if (tmp == 0) {
            ans += s[i].f;
            continue;
        }

        vis[tmp] = 1;
    }

    cout << m - ans << endl;
    return 0;
}