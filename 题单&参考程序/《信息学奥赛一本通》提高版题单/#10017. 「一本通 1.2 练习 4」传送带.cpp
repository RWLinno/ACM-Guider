#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define double long double
using namespace std;
const int N = 2e5 + 7;
const int mod = 1e9 + 7;
const double eps = 1e-9;

//int read(){   int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-') f=f*-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}return x*f;}
inline double Abs(double x) {
    return x < 0 ? -x : x;
}
struct P {
    double x, y;
    P operator - (P b) {
        return (P) {
            x - b.x, y - b.y
        };
    }
    P operator + (P b) {
        return (P) {
            x + b.x, y + b.y
        };
    }
    P operator * (double d) {
        return (P) {
            x *d, y *d
        };
    }
    P operator / (double d) {
        return (P) {
            x / d, y / d
        };
    }
    bool operator == (P b) {
        return Abs(x - b.x) < eps && Abs(y - b.y) < eps;
    }
} s[5];

double p, r, q, ans = inf;

inline double getdis(P a, P b) { //获取两点距离
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

inline double getans(P E, P F) { //获取时间
    double res = getdis(s[1], E) / p + getdis(E, F) / r + getdis(F, s[4]) / q;
    ans = min(ans, res);
    return res;
}

signed main() {
    for (int i = 1; i <= 4; i++)
        scanf("%lf%lf", &s[i].x, &s[i].y);

    scanf("%lf%lf%lf", &p, &q, &r); //t=dis<A,E>/P+dis<E,F>/R+dis<F,D>/Q;
    P L1 = s[1], R1 = s[2], M1, M2; //三分取E点

    while (getdis(R1, L1) > 0.0000000001) {
        M1 = L1 + (R1 - L1) / 3.0; //取AB三分之一处
        M2 = R1 - (R1 - L1) / 3.0; //取AB三分之二处
        P L2 = s[3], R2 = s[4], M3, M4; //三分取F点

        while (getdis(R2, L2) > 0.0000000001) {
            M3 = L2 + (R2 - L2) / 3.0, M4 = R2 - (R2 - L2) / 3.0;

            if (getans(M1, M3) < getans(M1, M4))
                R2 = M4;
            else
                L2 = M3; //缩左点
        }

        if (getans(M1, L2) < getans(M2, L2))
            R1 = M2;
        else
            L1 = M1;
    }

    if (s[1] == s[2]) { //如果一开始AB是一个点
        P L2 = s[3], R2 = s[4], M3, M4; //三分取F点

        while (getdis(R2, L2) > 0.0000000001) {
            M3 = L2 + (R2 - L2) / 3.0, M4 = R2 - (R2 - L2) / 3.0;

            if (getans(s[1], M3) < getans(s[1], M4))
                R2 = M4;
            else
                L2 = M3; //缩左点
        }
    }

    printf("%.2lf", ans);
    return 0;
}