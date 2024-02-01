#include <bits/stdc++.h>
using namespace std;

int vx[10][10], vy[10][10], vc[10][10], mp[10][10], ans = -1;
struct Node {
    int num, cnt;
} so[10];

bool cmp(Node x, Node y) {
    return x.cnt > y.cnt;
}

void dfs(int x, int y) {
    int sx = x;
    x = so[sx].num;

    if (sx == 9) {
        int sum = 0;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                sum += mp[i][j] * min(10 - abs(i - 4), 10 - abs(j - 4));
            }
        }

        ans = max(ans, sum);
        return;
    }

    if (y == 9) {
        dfs(sx + 1, 0);
        return;
    }

    if (mp[x][y])
        dfs(sx, y + 1);
    else
        for (int i = 1; i <= 9; i++) {
            if (!vx[x][i] && !vy[y][i] && !vc[x / 3 * 3 + y / 3][i]) {
                vx[x][i] = 1;
                vy[y][i] = 1;
                vc[x / 3 * 3 + y / 3][i] = 1;
                mp[x][y] = i;
                dfs(sx, y + 1);
                vx[x][i] = 0;
                vy[y][i] = 0;
                vc[x / 3 * 3 + y / 3][i] = 0;
                mp[x][y] = 0;
            }
        }
}

int main() {
    for (int i = 0; i < 9; i++) {
        so[i].num = i;

        for (int j = 0; j < 9; j++) {
            cin >> mp[i][j];

            if (mp[i][j]) {
                so[i].cnt++;
                vx[i][mp[i][j]] = 1;
                vy[j][mp[i][j]] = 1;
                vc[i / 3 * 3 + j / 3][mp[i][j]] = 1;
            }
        }
    }

    sort(so, so + 9, cmp);
    dfs(0, 0);
    printf("%d", ans);
    return 0;
}