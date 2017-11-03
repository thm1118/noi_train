#include<cstdio>
#include<iostream>

/**
 * 两人一起行走 来动规 迭代实现，来自洛谷
 *
 * */

using namespace std;
int dp[12][12][12][12], a[12][12], maxn, ans = 0;

int main() {
    int n;
    cin >> n;
    int x, y, val;
    while (1) {
        scanf("%d%d%d", &x, &y, &val);
        if (x == 0 && y == 0 && val == 0)break;
        a[x][y] = val;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                for (int l = 1; l <= n; l++) {
                    dp[i][j][k][l] = max(dp[i - 1][j][k - 1][l],
                                         max(dp[i - 1][j][k][l - 1],
                                             max(dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l -1])))
                                     + a[i][j] + a[k][l];
                    if (i == k && j == l) dp[i][j][k][l] -= a[i][j];
                }
            }
        }
    }
    cout << dp[n][n][n][n];
    return 0;
} 