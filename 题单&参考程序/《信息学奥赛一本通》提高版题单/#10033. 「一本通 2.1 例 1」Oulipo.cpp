#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int base = 131;
const int mod = 1e16 + 7;
int bb[1000005], sum[1000005], hs;

int get_hs(int i, int l) {
    return sum[i + l - 1] - sum[i - 1] * bb[l];
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string A, B;
    cin >> A;
    cin >> B;
    int lena = A.length(), lenb = B.length(), ans = 0;

    for (int i = 0; i < lenb; i++) {
        hs = (hs * base + B[i] - 'A' + 1);
    }

    bb[0] = 1;

    for (int i = 1; i <= lena; i++) {
        bb[i] = bb[i - 1] * base;
        sum[i] = (sum[i - 1] * base + A[i - 1] - 'A' + 1);
    }

    for (int i = lenb; i <= lena; i++) {
        if (sum[i] - sum[i - lenb]*bb[lenb] == hs) {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}