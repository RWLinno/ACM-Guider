#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;

inline bool is_pri(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return 0;

    return 1;
}

int S, A, g[6][6], hz[N], qz[N];
int jx1, jx2, sum, L[10], R[10], p[6] = {1, 10, 100, 1000, 10000, 100000};

inline void outp() {
    for (int i = 1; i <= 5; ++i)
        printf("%d\n", L[i]);

    printf("\n");
}

inline void add(int x) {
    int a[6] = {0, x / 10000, x / 1000 % 10, x / 100 % 10, x / 10 % 10, x % 10};

    if (a[1] + a[2] + a[3] + a[4] + a[5] != S)
        return;

    if (!is_pri(x))
        return;

    int i = x;
    qz[i / 10000] = qz[i / 1000] = qz[i / 100] = qz[i / 10] = qz[i] = 1;
    hz[i % 10000] = hz[i % 1000] = hz[i % 100] = hz[i % 10] = hz[i] = 1;
}

void dfs(int x, int y) {
    if (y == 6)
        y = 1, x += 1;

    if (x == 6) {
        ++sum;
        outp();
        return;
    }

    bool ok1, ok2, ok3, ok4;

    for (int i = 0; i <= 9; ++i) {
        ok1 = qz[L[x] * 10 + i];
        ok2 = qz[R[y] * 10 + i];
        ok3 = ((x != y) || (x == y && qz[jx1 * 10 + i]));
        ok4 = ((x + y != 6) || (x + y == 6 && hz[jx2 + i * p[x - 1]]));

        if (!(ok1 && ok2 && ok3 && ok4))
            continue;

        L[x] = L[x] * 10 + i;
        R[y] = R[y] * 10 + i;

        if (x == y)
            jx1 = jx1 * 10 + i;

        if (x + y == 6)
            jx2 = jx2 + i * p[x - 1];

        dfs(x, y + 1);
        L[x] /= 10;
        R[y] /= 10;

        if (x == y)
            jx1 /= 10;

        if (x + y == 6)
            jx2 -= i * p[x - 1];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> S >> A;

    for (int i = 10003; i <= 99999; i += 2)
        add(i);

    memset(g, -1, sizeof(g));
    g[1][1] = A;
    L[1] = R[1] = jx1 = A;
    dfs(1, 2);

    if (sum == 0)
        cout << "NONE\n";

    return 0;
}