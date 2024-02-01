#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
#define pii pair<int,int>
#define mk make_pair
#define fi first
#define se second
using namespace std;
const int N = 52, M = 10007;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

/*
1.建图，然后以1,1为源点开始跑，寻找下一个结点
2.不允许返回上一个点，对从s出发当前阶段的每个点取最短路
*/
int n, m, goal;
vector<pii>G[N][N];
int vis[N][N][M];
char mp[N][N];
string str;

struct X {
    int x, y, now, step;
};
queue<X>q;

void Solve() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }

    cin >> str;
    str += '*';
    goal = str.length();

    for (int i = 1; i <= n; i++) {
        for (int j = 1, sx, sy; j <= m; j++) { //对每个点进行上下左右连边
            sx = i, sy = j;

            while (sx > 0 && mp[sx][sy] == mp[i][j])
                sx--;

            if (sx > 0)
                G[i][j].emplace_back(mk(sx, sy));

            sx = i, sy = j;

            while (sx <= n && mp[sx][sy] == mp[i][j])
                sx++;

            if (sx <= n)
                G[i][j].emplace_back(mk(sx, sy));

            sx = i, sy = j;

            while (sy > 0 && mp[sx][sy] == mp[i][j])
                sy--;

            if (sy > 0)
                G[i][j].emplace_back(mk(sx, sy));

            sx = i, sy = j;

            while (sy <= m && mp[sx][sy] == mp[i][j])
                sy++;

            if (sy <= m)
                G[i][j].emplace_back(mk(sx, sy));
        }
    }

    q.push((X) {
        1, 1, 0, 1
    });

    while (!q.empty()) {
        X fro = q.front();
        q.pop();

        //  cout<<fro.x<<" "<<fro.y<<" "<<mp[fro.x][fro.y]<<" "<<fro.now<<" "<<fro.step<<"\n";
        if (vis[fro.x][fro.y][fro.now] && vis[fro.x][fro.y][fro.now] <= fro.step)
            continue;//前面阶段已经走过这个点了

        vis[fro.x][fro.y][fro.now] = fro.step;

        while (mp[fro.x][fro.y] == str[fro.now]) {
            fro.step++;
            fro.now++;

            if (fro.now == goal) {
                cout << fro.step - 1 << "\n";
                return;
            }
        }

        for (auto to : G[fro.x][fro.y]) {
            q.push((X) {
                to.fi, to.se, fro.now, fro.step + 1
            });
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    int T = 1;

    //cin>>T;
    while (T--) {
        Solve();
    }

    return 0;
}