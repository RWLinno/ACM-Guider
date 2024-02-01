#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

int n, m, a[N];

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    cin >> n >> m;
    int tmp = 0, cnt = 1;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];

        if (tmp + a[i] > m) {
            tmp = a[i];
            cnt++;
        } else
            tmp += a[i];
    }

    cout << cnt << "\n";
    return 0;
}