/**
 *  硬币问题 递归版
 * */
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

vector<int> cache;

int getCoinsMinCount(int money){
    // 金额0元 ，返回0 个硬币
    if(money == 0) return 0;
    // 负数金额，来自尝试金额 与硬币差值可能为负，就无法用到这个硬币。返回个极大值。
    if(money < 0) return INT_MAX;

    // 递归 需要优化 剪枝
    if(cache[money] != -1){
        return cache[money];
    }
    // 分别尝试 取三种面值 硬币 各1个 后的 最小硬币数量，再加上自身一个。
    int minCount = min(getCoinsMinCount(money - 1), min(getCoinsMinCount(money - 3), getCoinsMinCount(money - 5))) + 1;
    cache[money] = minCount;
    return minCount;
}

int main(){
    // 金额 n 元
    int n ;
    cin >> n;
    clock_t t;
    t = clock();

    cache = vector<int>(n + 1, -1);
    cout << "money " << n << " " << "need coins count at a minimum is " << getCoinsMinCount(n) << endl;

    cout << "It took seconds " << (float)(clock() - t)/CLOCKS_PER_SEC << endl;

    return 0;
}
