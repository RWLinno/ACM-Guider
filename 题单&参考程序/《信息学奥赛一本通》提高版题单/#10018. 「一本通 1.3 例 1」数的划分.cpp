#include <bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long ll;

int ans = 0, n, k;

void dfs(int lf, int num, int step) {
    if (step == k) {
        if (lf == 0) {
            ans++;
        }

        return;
    }

    for (int i = num; i <= lf; i++) {
        dfs(lf - i, i, step + 1);
    }

    return;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    cin >> k;

    for (int i = 1; i <= n; i++) {
        dfs(n - i, i, 1);
    }

    cout << ans << endl;
    return 0;
}