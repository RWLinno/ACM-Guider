#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 7;

int n, a[maxn], L;
double b[maxn], sum[maxn];

bool check(double x) {
    for (int i = 1; i <= n; i++)
        b[i] = a[i] - x; //新数组

    for (int j = 1; j <= n; j++)
        sum[j] = sum[j - 1] + b[j]; //前缀和

    double minz = 0; //记录前i个数最小值

    for (int i = L; i <= n; i++) { //
        minz = min(minz, sum[i - L]);

        if (sum[i] - minz >= 0)
            return true;
    }

    return false;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> L;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] *= 1000;
    }

    double l = 0, r = 1e15 + 7, mid;

    while (r - l > 1e-5) {
        mid = (l + r) / 2;

        if (check(mid))
            l = mid; //平均值在上
        else
            r = mid; //平均值在下
    }

    cout << (int)(l + 0.0001) << endl;
    return 0;
}