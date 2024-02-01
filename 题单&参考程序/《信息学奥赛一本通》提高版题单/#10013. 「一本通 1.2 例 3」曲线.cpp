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

int n, t, a[maxn], b[maxn], c[maxn];

double fc(double x, int y) {
    return (double)a[y] * x * x + (double)b[y] * x + (double)c[y];
}

double check(double x) {
    double mx = -10000000.0;

    for (int i = 1; i <= n; i++) {
        mx = max(mx, fc(x, i));
    }

    return mx;
}

signed main() {
    read(t);

    while (t--) {
        read(n);

        for (int i = 1; i <= n; i++) {
            read(a[i]);
            read(b[i]);
            read(c[i]);
        }

        double l = 0, r = 1000000, midl, midr, tmp;

        while (fabs(r - l) > 1e-9) {
            tmp = (r - l) / 3;
            midl = l + tmp;
            midr = r - tmp;

            if (check(midl) > check(midr))
                l = midl;
            else
                r = midr;
        }

        printf("%.4lf\n", check(l));
    }

    return 0;
}
