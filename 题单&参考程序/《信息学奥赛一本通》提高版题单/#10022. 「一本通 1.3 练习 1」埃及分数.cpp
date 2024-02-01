#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 1e7 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
//void write(int x){if(x>9) write(x/10);putchar(x%10+'0');}

int a, b, way[N], ans[N], best = N, lim, flag;

inline void dfs(int x, int y, int dep) { //ID迭代加深搜索
    int l1, l2;
    l1 = max(way[dep - 1] + 1, y / x); //分母最小值
    l2 = min(y * (lim - dep + 1) / x, best - 1); //分母最大值

    //cout<<x<<" "<<y<<" "<<dep<<" "<<l1<<" "<<l2<<" !!\n";
    for (int i = l1; i <= l2; i++) {
        int xx = x, yy = y;
        way[dep] = i;
        xx = xx * i - yy;

        if (x < 0)
            continue;

        yy = yy * i;

        if (dep < lim)
            dfs(xx, yy, dep + 1);

        if (i < best && xx == 0) {
            flag = 1;
            best = i;

            for (int j = 1; j <= lim; j++)
                ans[j] = way[j];
        }
    }
}

void Solve() {
    cin >> a >> b;
    flag = 0;

    while (!flag) {
        ++lim;
        dfs(a, b, 1);
    }

    for (int i = 1; i <= lim; i++)
        cout << ans[i] << " ";
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

    //  cerr<<clock()*1.0/CLOCKS_PER_SEC<<endl;
    return 0;
}