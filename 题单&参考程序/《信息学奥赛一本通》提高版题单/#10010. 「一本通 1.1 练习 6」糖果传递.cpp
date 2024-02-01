#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 1e6 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, sum = 0, a[N], s[N], ans = 0, tmp;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    int avg = sum / n; //每个人最终能拿的糖果

    for (int i = 1; i <= n; i++) {
        s[i] = a[i] - avg;
        s[i] += s[i - 1];
    }

    sort(s + 1, s + 1 + n);
    int t = s[(n + 1) / 2];

    for (int i = 1; i <= n; i++)
        ans += abs(t - s[i]);

    cout << ans << "\n";
    return 0;
}