#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define mk make_pair
#define pii pair<int,int>
using namespace std;
const int N = 507;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, m, dep[N][N];
char val[] = {'/', '\\', '/', '\\'}, mp[N][N];
int biasx[] = {-1, 0, 0, -1}, biasy[] = {0, 0, -1, -1};
int dx[] = {-1, 1, 1, -1}, dy[] = {1, 1, -1, -1};
deque<pii>q;

void Solve() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }

    for (int i = 1; i <= n + 1; i++) {
        for (int j = 1; j <= m + 1; j++)
            dep[i][j] = inf;
    }

    dep[1][1] = 0;
    q.push_back(mk(1, 1));

    while (!q.empty()) {
        pii fro = q.front();
        q.pop_front();

        if (fro.first == n + 1 && fro.second == m + 1)
            break;

        for (int d = 0; d < 4; d++) {
            int nx = fro.first + dx[d], ny = fro.second + dy[d];

            if (nx < 1 || ny < 1 || nx > n + 1 || ny > m + 1 || dep[nx][ny] < dep[fro.first][fro.second] + 1)
                continue;

            int xx = fro.first + biasx[d], yy = fro.second + biasy[d];

            if (mp[xx][yy] == val[d]) {
                dep[nx][ny] = dep[fro.first][fro.second];
                q.push_front(mk(nx, ny));
            } else {
                dep[nx][ny] = dep[fro.first][fro.second] + 1;
                q.push_back(mk(nx, ny));
            }
        }
    }

    if (dep[n + 1][m + 1] == inf)
        cout << "NO SOLUTION\n";
    else
        cout << dep[n + 1][m + 1];
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