#include <bits/stdc++.h>
#define debug(x) cout<<"x="<<x<<endl
#define int long long
using namespace std;
const int maxn = 1e5 + 7;
const int mod = 1e9 + 7;
typedef long long ll;

//ifstream mycin("in.txt");
//ofstream mycout("out.txt");

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

int n, m, a[maxn];

bool check(int x) {
    int num = 1, now = a[1], idx = 1;

    for (int i = 2; i <= n; i++) {
        if (a[i] - a[idx] >= x)
            num++, idx = i;
    }

    if (num >= m)
        return true;
    else
        return false;
}

signed main() {
    read(n);
    read(m);

    for (int i = 1; i <= n; i++)
        read(a[i]);

    sort(a + 1, a + 1 + n);
    int l = 0, r = 1e9 + 7, mid;

    while (r - l > 1) {
        mid = l + r >> 1;

        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    cout << l << endl;
    return 0;
}
