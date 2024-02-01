#include <bits/stdc++.h>
using namespace std;

struct E {
    int l, r;
} s[1005];

int n;

bool cmp(E a, E b) {
    return a.r < b.r;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> s[i].l >> s[i].r;
    }

    sort(s + 1, s + 1 + n, cmp);
    int ans = 0, tim = 0;

    for (int i = 1; i <= n; i++) {
        if (s[i].l >= tim) {
            tim = s[i].r;
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}