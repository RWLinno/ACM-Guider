#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define int long long
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}

string str = "12345678", goal = "";

struct X {
    string s, v;
    int step;
};

int a[10];
map<string, int>mp;
queue<X>q;
vector<string>ans;

void Solve() {
    for (int i = 0; i < 8; i++) {
        cin >> a[i];
        goal += (char)(a[i] + '0');
    }

    q.push((X) {
        str, "", 1
    });

    while (!q.empty()) {
        X fro = q.front();
        q.pop();

        //  cout<<fro.s<<" "<<fro.v<<" "<<fro.step<<"\n";
        if (mp[fro.s])
            continue;

        mp[fro.s] = fro.step;

        if (fro.s == goal) {
            cout << fro.v.length() << "\n";
            ans.emplace_back(fro.v);
            break;
        }

        string s1 = fro.s, s2 = fro.s, s3 = fro.s;

        for (int i = 0; i < 8; i++)
            s1[i] = fro.s[7 - i]; //交换上下两行

        for (int i = 1; i < 4; i++)
            s2[i] = fro.s[i - 1];

        s2[0] = fro.s[3]; //将最右边的一列插入最左边

        for (int i = 4; i < 7; i++)
            s2[i] = fro.s[i + 1];

        s2[7] = fro.s[4];
        s3[1] = fro.s[6]; //中间顺时针旋转
        s3[2] = fro.s[1];
        s3[5] = fro.s[2];
        s3[6] = fro.s[5];
        q.push((X) {
            s1, fro.v + "A", fro.step + 1
        });
        q.push((X) {
            s2, fro.v + "B", fro.step + 1
        });
        q.push((X) {
            s3, fro.v + "C", fro.step + 1
        });
    }

    sort(ans.begin(), ans.end());
    cout << ans[0];
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("1.out","w",stdout);
    int T = 1;

    //cin>>T;
    while (T--) {
        Solve();
    }

    return 0;
}