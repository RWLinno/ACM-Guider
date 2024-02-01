#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define int long long
using namespace std;
const int N = 2e5 + 7, M = 105;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, h, res, a[M], b[M], t[M], sum[M];
int mx[N], dp[M][N], xz[M][N];

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    cin >> n >> h;
    h *= 12;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++)
        cin >> b[i];

    sum[1] = 0;

    for (int i = 2; i <= n; i++) {
        cin >> t[i];
        sum[i] = sum[i - 1] + t[i];
    }

    for (int i = 1; i <= n; i++) {
        mx[i] = 0;

        while (a[i] > 0 && mx[i] <= h) { //预处理每个湖钓j次的收益
            mx[i]++;
            xz[i][mx[i]] = xz[i][mx[i] - 1] + a[i];
            a[i] -= b[i];
        }
    }

    for (int i = 1; i <= n; i++) { //枚举每一个湖
        for (int j = sum[i]; j <= h; j++) { //枚举体力
            for (int k = 0; k <= j - sum[i]; k++) { //枚举用于i湖钓鱼的体力
                dp[i][j] = max(dp[i][j], dp[i - 1][j - t[i] - k] + xz[i][k]);
                //  dp[i][j]=max(dp[i][j],dp[i-1][j-t[i]-k]+k*(a[i]+a[i]-(k-1)*b[i])/2);
                res = max(res, dp[i][j]);
            }
        }
    }

    cout << res << "\n";
    return 0;
}