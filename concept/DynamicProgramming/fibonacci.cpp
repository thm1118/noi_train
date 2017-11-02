#include <iostream>
using namespace std;

/**
 * 斐波那契数列 迭代版
 * */
int main(){
    int n;
    cin >> n;

    long fibonacci[n];
    fibonacci[0] = 1;
    fibonacci[1] = 2;

    for(int i = 2; i < n; i++){
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
    }

    cout << fibonacci[n-1];

    return 0;
}

