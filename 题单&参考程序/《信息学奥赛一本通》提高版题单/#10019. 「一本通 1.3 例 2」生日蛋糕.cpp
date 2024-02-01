#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int maxn = 1e4 + 7;

int n, m, fp[maxn], sum[maxn], S, R, ans = 2e9;

void dfs(int dep, int V, int S, int pr, int ph) {
    //cout<<dep<<" "<<V<<" "<<H<<" "<<pr<<" "<<ph<<endl;
    if (dep == m) {
        if (V == n)
            ans = min(ans, S);

        return;
    }

    if (V > n || S >= ans)
        return;

    if (S + 2 * (n - V) / pr >= ans)
        return;

    if (pr * pr * ph * (m - dep) + V < n)
        return;

    for (int r = pr - 1; r >= m - dep; r--) {
        for (int h = ph - 1; h >= m - dep; h--) {
            dfs(dep + 1, V + r * r * h, dep == 0 ? (S + 2 * r * h + r * r) : S + 2 * r * h, r, h);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    dfs(0, 0, 0, sqrt(n) + 1, n + 1);

    if (ans == 2e9)
        cout << 0 << "\n";
    else
        cout << ans << "\n";

    return 0;
}