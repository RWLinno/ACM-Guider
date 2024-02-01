#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1007;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X {
    int x, y;
};
int n, sg = 0, sf = 0, mp[N][N], vis[N][N];
int xx[] = {1, 0, -1, 1, 0, -1, 1, -1}, yy[] = {1, 1, 1, -1, -1, -1, 0, 0};

void bfs(int sx, int sy) {
    queue<X>q;
    q.push((X) {
        sx, sy
    });
    int flag = 0;

    while (!q.empty()) {
        X fro = q.front();
        q.pop();

        if (vis[fro.x][fro.y])
            continue;

        vis[fro.x][fro.y] = 1;

        //  cout<<fro.x<<" "<<fro.y<<" "<<flag<<"\n";
        for (int d = 0; d < 8; d++) {
            int nx = fro.x + xx[d], ny = fro.y + yy[d];

            if (nx < 1 || ny < 1 || nx > n || ny > n)
                continue;

            if (flag == 1 && mp[nx][ny] < mp[fro.x][fro.y] || flag == 2 && mp[nx][ny] > mp[fro.x][fro.y])
                flag = 3;

            if (!flag && mp[nx][ny] > mp[fro.x][fro.y]) { //这片区域是山谷
                flag = 1;
            } else if (!flag && mp[nx][ny] < mp[fro.x][fro.y]) { //这篇区域是山峰
                flag = 2;
            }

            if (mp[nx][ny] == mp[fro.x][fro.y])
                q.push((X) {
                nx, ny
            });
        }
    }

    if (flag == 1)
        sg++;
    else if (flag == 2)
        sf++;
    else if (!flag)
        sg++, sf++;

    //  cout<<sx<<" "<<sy<<" "<<flag<<" "<<sf<<" "<<sg<<"\n";
    return;
}

void Solve() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> mp[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!vis[i][j])
                bfs(i, j); //遍历该连通块
        }
    }

    cout << sf << " " << sg << "\n";
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    int T = 1;

    //cin>>T;
    while (T--) {
        Solve();
    }

    return 0;
}