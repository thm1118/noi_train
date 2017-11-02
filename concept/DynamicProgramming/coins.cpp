#include <cstring>
#include <iostream>
#include <ctime>

using namespace std;

/**
 *  硬币问题
 *  如果我们有面值为1元、3元和5元的硬币若干枚，如何用最少的硬币凑够11元？
 *  -- 表格迭代方式
 * */

int main() {
    // 金额 n 元
    int n ;
    cin >> n;

    clock_t t;
    t = clock();

    // 硬币三种面值
    int coins[3] = {1, 3, 5};
    // 分别记录 目前金额为1,2,3..元的 需要的最小硬币数量 的对应数组。 注意这里包括0 - n 元；
    int minCoinCount[n + 1];

    // 已知0元对应了 0个硬币
    minCoinCount[0] = 0;
    //初始化其余 金额对应最小硬币数量 数组，都为金额数，相当于是最大硬币数+1个，是个不可能达到的值。
    memset(minCoinCount + 1, n + 1, sizeof(minCoinCount) - 1);

    // 金额1 -n 的 循环
    for (int i = 1; i <= n; i++) {
        // 每个金额 分别尝试 使用至少1个 某硬币
        for (int coinIndex = 0; coinIndex < 3; coinIndex++) {
            /**
             * 当尝试使用某个硬币时， 这个硬币就占据了数量 1；
             * 如果当前金额 可能小于当前硬币面值，就不可能用到这个硬币
             *
             * 此时用当前金额 减去这个硬币面值，差值 需要的最小硬币数量 前面已经算过（因为金额是从小到大 循环，并且给定了0元0个硬币的初始化）
             * 前面算过的最小硬币数量 + 1 个 如果 小于minCoinsCount当前金额对应值（可能是初始值，不可能达到的最大硬币数量），就替换之。
             * */
            if (i >= coins[coinIndex] && minCoinCount[i - coins[coinIndex]] + 1 < minCoinCount[i])
                minCoinCount[i] = minCoinCount[i - coins[coinIndex]] + 1;
        }
    }

    cout << "money " << n << " " << "need coins count at a minimum is " << minCoinCount[n];
    cout << "It took seconds " << (float)(clock() - t)/CLOCKS_PER_SEC << endl;

    return 0;
}
