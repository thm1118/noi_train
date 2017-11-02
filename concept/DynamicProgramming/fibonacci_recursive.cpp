#include <iostream>
#include <vector>
using namespace std;
/**
 *
 * 斐波那契数列 递归版
 * */

vector<long> cache;

long getFibonacci(int index){
    if(index == 1) return 1;
    if(index == 2) return 2;
    if(cache[index] == -1) cache[index] = getFibonacci(index - 1) + getFibonacci(index - 2);
    return cache[index];
}

int main(){
    int n;
    cin >> n;

    cache = vector<long>(n+1, -1);
    cout << getFibonacci(n) << endl;
    return 0;
}
