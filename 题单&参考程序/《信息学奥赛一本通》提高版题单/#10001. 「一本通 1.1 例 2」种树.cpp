#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 7;

struct X {
    int l, r, need;
} s[maxn];

bool cmp(X a, X b) {
    if (a.r != b.r)
        return a.r < b.r;

    return a.l < b.l;
}

int n, h, ans, vis[maxn];

void work() {
    memset(vis, 0, sizeof(vis));

    for (int i = 1; i <= h; i++) { //对所有查询区间
        int r = s[i].r; //从最右边开始

        while (s[i].need > 0) {
            if (vis[r]) {
                r--;    //这个地方已经种过树了
                continue;
            }

            s[i].need--;
            vis[r] = 1;

            for (int j = i + 1; j <= h; j++) { //对于剩下询问，减去所需要的一棵
                if (s[j].l <= r && r <= s[j].r)
                    s[j].need--;

                //  else break;
            }

            r--;
            ans++;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> h;

    for (int i = 1; i <= h; i++) {
        cin >> s[i].l >> s[i].r >> s[i].need;
    }

    sort(s + 1, s + 1 + h, cmp);
    work();
    cout << ans << endl;
    return 0;
}