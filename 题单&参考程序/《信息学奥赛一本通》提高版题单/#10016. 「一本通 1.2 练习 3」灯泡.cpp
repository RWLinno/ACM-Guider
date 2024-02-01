#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
double H, h, D, Y, K, J; //Y是边界距离,K是离墙距离，J是墙上影子距离

double fc(double k) { //k为离墙距离
    double ans = (D - k) + (H - (H - h) * D / k);
    //  cout<<k<<" "<<ans<<"\n";
    return ans;
}

signed main() {
    //  ios::sync_with_stdio(0);
    //  cin.tie(0);cout.tie(0);
    //  freopen("in.cpp","r",stdin);
    //  freopen("out.cpp","w",stdout);
    int t;
    cin >> t;

    while (t--) {
        cin >> H >> h >> D;
        double L = D * (H - h) / H, R = D, M1, M2;

        while (R - L > 1e-6) {
            M1 = L + (R - L) / 3;
            M2 = R - (R - L) / 3;

            if (fc(M1) <= fc(M2))
                L = M1;
            else
                R = M2;
        }

        printf("%.3lf\n", fc(L));
    }

    return 0;
}