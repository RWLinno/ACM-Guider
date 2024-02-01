#include <bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long ll;
const int maxn = 1005;

int n;
struct E {
    int x, y, id;
} s[maxn];

bool cmp(E a, E b) {
    return min(a.x, b.y) < min(a.y, b.x);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++)
        s[i].id = i;

    for (int i = 1; i <= n; i++)
        cin >> s[i].x;

    for (int i = 1; i <= n; i++)
        cin >> s[i].y;

    sort(s + 1, s + 1 + n, cmp);
    int now1 = 0, now2 = 0, sum = 0; //两车间当前加工时间

    for (int i = 1; i <= n; i++) {
        now2 -= s[i].x;

        if (now2 < 0)
            now2 = 0;

        now2 += s[i].y;
        sum += s[i].x;
    }

    sum += now2;
    cout << sum << "\n";

    for (int i = 1; i <= n; i++) {
        cout << s[i].id << " ";
    }

    return 0;
}