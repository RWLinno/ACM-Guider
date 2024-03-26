#include <bits/stdc++.h>
//#define int long long
using namespace std;
typedef long long ll;

int n;
string op, name;
map<string, int>mp;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> op;
        getline(cin, name);

        if (op == "add")
            mp[name] = 1;
        else {
            if (mp[name])
                puts("yes");
            else
                puts("no");
        }
    }

    return 0;
}