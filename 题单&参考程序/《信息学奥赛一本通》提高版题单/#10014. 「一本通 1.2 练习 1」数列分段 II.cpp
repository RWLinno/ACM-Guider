#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e5 + 7;

inline void read(int &data) {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = f * -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }

    data = x * f;
}

int n, m, a[maxn], ans, s;
int l, r = 1e9 + 7, mid;

bool check(int x) {
    int num = 1, sum = 0;

    for (int i = 1; i <= n; i++) {
        if (sum + a[i] > x) {
            sum = a[i];
            num++; //新的一段
        } else {
            sum += a[i];
        }
    }

    if (num <= m)
        return true;
    else
        return false;
}

signed main() {
    read(n);
    read(m);

    for (int i = 1; i <= n; i++) {
        read(a[i]);
        l = max(a[i], l);
    }

    while (l <= r) {
        mid = (r + l) >> 1;

        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else
            l = mid + 1;
    }

    cout << ans << endl;
    return 0;
}