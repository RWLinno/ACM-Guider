#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 105, M = 1e5 + 7;

struct Nod {
    int x1, x2, y1, y2, c;
    friend bool operator <(Nod A, Nod B) {
        if (A.y1 != B.y1)
            return A.y1 < B.y1;

        return A.y2 < B.y2;
    }
} a[N];

int xx[M], yy[M];
int b[N][N], n, m, ans = inf;

bool find(int d) { //查询当前块是否涂过颜色
    for (int i = 0; i < n; ++i) {
        if (b[d][i] && !xx[i])
            return false;
    }

    return true;
}

void dfs(int cnt, int f, int sum) {
    if (cnt >= ans)
        return;

    if (sum == n) {
        ans = cnt;
        return;
    }

    for (int i = 0; i < m; ++i) { //枚举每一种颜色
        int h = 0;

        if (yy[i] && i != f) {
            for (int j = 0; j < n; ++j) {
                if (!xx[j] && a[j].c == i && find(j)) {
                    xx[j] = 1;
                    h++;
                } else if (xx[j] && a[j].c == i)
                    xx[j]++;
            }

            if (h > 0)
                dfs(cnt + 1, i, sum + h);

            for (int j = n - 1; j >= 0; --j) { //回溯
                if (xx[j] == 1 && a[j].c == i && find(j)) {
                    xx[j] = 0;
                    h--;
                } else if (xx[j] > 1 && a[j].c == i)
                    xx[j]--;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> a[i].x1 >> a[i].x2 >> a[i].y1 >> a[i].y2 >> a[i].c;
        yy[a[i].c]++;
    }

    m = 20;
    sort(a, a + n);

    for (int i = 1; i < n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (a[i].x1 == a[j].y1 && ((a[i].x2 >= a[j].x2 && a[i].x2 <= a[j].y2) || (a[i].y2 >= a[j].x2 &&
                                       a[i].y2 <= a[j].y2))) {
                b[i][j] = 1;
            }
        }
    }

    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}