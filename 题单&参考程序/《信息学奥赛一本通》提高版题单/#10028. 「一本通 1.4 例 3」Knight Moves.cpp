#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1007;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

struct X {
    int x, y, step;
};
int n, L, sx, sy, dx, dy, vis[N][N];
int xx[] = {1, 1, -1, -1, 2, -2, 2, -2}, yy[] = {2, -2, 2, -2, 1, 1, -1, -1};
queue<X>q;

void Solve(int n) {
    memset(vis, 0, sizeof(vis));

    while (q.size())
        q.pop();

    cin >> L;
    cin >> sx >> sy >> dx >> dy;
    q.push((X) {
        sx, sy, 1
    });

    while (!q.empty()) {
        X fro = q.front();
        q.pop();

        //  cout<<fro.x<<" "<<fro.y<<" "<<fro.step<<" !\n";
        if (fro.x < 0 || fro.y < 0 || fro.x > L - 1 || fro.y > L - 1 || vis[fro.x][fro.y])
            continue;

        vis[fro.x][fro.y] = fro.step;

        if (fro.x == dx && fro.y == dy) {
            cout << fro.step - 1 << "\n";
            return;
        }

        for (int d = 0; d < 8; d++) {
            int sx = fro.x + xx[d], sy = fro.y + yy[d];
            q.push((X) {
                sx, sy, fro.step + 1
            });
        }
    }
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);;
    int T = 1;
    cin >> T;

    while (T--) {
        Solve(T);
    }

    return 0;
}