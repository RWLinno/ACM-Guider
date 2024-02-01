#include <bits/stdc++.h>
using namespace std;

inline void read(int &data) {
    int x = 0, f = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = f * -1;

        ch = getchar();
    }

    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }

    data = x * f;
}

bool cmp(int a, int b) {
    return a > b;
}

int flag = 0, tot, len, cnt;
int n, a[105], d, sum = 0, vis[105], nx[105];

void dfs(int left, int step, int num) { //当前组剩余长度、当前组数、上次选的序号
    if (flag)
        return; //已经找到答案了

    if (left == 0 && step == tot) { //每一组都分完了
        flag = 1;
        return;
    }

    if (left == 0) {
        dfs(len, step + 1, 0); //left等于0，重新分组
        return;
    }

    //优化4:二分找第一个 木棍长度不大于未拼长度的位置
    int l = num + 1, r = cnt, mid;

    while (l < r) {
        mid = (l + r) >> 1;

        if (a[mid] <= left)
            r = mid;
        else
            l = mid + 1;
    }

    for (int i = l; i <= cnt; i++) { //从大到小选
        if (left >= a[i] && !vis[i]) { //大于木棍长度并且没被访问的情况
            vis[i] = 1; //这个长度的木棍已经用过了
            dfs(left - a[i], step, i);
            vis[i] = 0; //回溯

            if (flag)
                return; //找到答案推出循环

            if (left == a[i] || left == len)
                return; //优化？？

            i = nx[i]; //优化：直接跳到下一个长度不同的木棍

            if (i == cnt)
                return;
        }
    }

    return;
}

int main() {
    read(n);

    for (int i = 1; i <= n; i++) {
        read(d);

        if (d > 50)
            continue; //听说要过滤

        a[++cnt] = d; //cnt才是木棍总个数
        sum += d;
    }

    sort(a + 1, a + 1 + n, cmp); //重大到小排序
    nx[cnt] = cnt;

    for (int i = cnt - 1; i > 0; i--) {
        if (a[i] == a[i + 1])
            nx[i] = nx[i + 1];
        else
            nx[i] = i;
    }

    vis[1] = 1; //第一根木棍开始

    for (len = a[1]; len <= sum / 2; len++) { //要么两组，要么一组（不用拼）
        if (sum % len != 0)
            continue; //不被整除直接返回

        tot = sum / len; //要拼的组数
        dfs(len - a[1], 1, 1); //最大那个木棍肯定要用到

        if (flag) { //如果找到了答案
            printf("%d\n", len);
            return 0;
        }
    }

    printf("%d\n", sum);
    return 0;
}