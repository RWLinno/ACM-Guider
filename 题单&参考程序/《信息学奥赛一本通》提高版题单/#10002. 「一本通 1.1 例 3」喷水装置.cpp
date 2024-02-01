#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 15005;

struct C {
    double l, r;
} s[maxn];

int t, n, cnt, ans;
double L, w, x, r;

bool cmp(C a, C b) {
    if (a.l == b.l)
        return a.r > b.r;

    return a.l < b.l;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;

    while (t--) {
        cnt = 0;
        cin >> n >> L >> w;

        for (int i = 1; i <= n; i++) {
            cin >> x >> r;

            if (r * 2 <= w)
                continue;

            s[++cnt].l = x - sqrt(r * r - w * w / 4);
            s[cnt].r = x + sqrt(r * r - w * w / 4);
        }

        sort(s + 1, s + 1 + cnt, cmp);
        double idx = 0, mx = 0;

        for (ans = 1; ans <= cnt; ans++) { //最多是打开cnt个喷头
            for (int j = ans; j <= cnt; j++) {
                if (s[j].r > idx && s[j].l <= idx) { //达到要求更进一步
                    if (mx < s[j].r)
                        mx = s[j].r; //取能够到的最远距离
                }
            }

            idx = mx;

            if (idx >= L)
                break; //达到目的
        }

        if (idx >= L)
            cout << ans << "\n";
        else
            cout << -1 << "\n";
    }

    return 0;
}