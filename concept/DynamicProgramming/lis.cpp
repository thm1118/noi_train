#include <iostream>
#include <vector>

using namespace std;
vector<int> int_list;
vector<int> cache;

//int getLis(size_t index){
//    if(index == 0) return 1;
//    if(cache[index] != -1) return cache[index];
//
//    if(int_list[index] > int_list[index - 1]) {
//        int maxLength = max(1, getLis(index - 1) + 1);
//        cache[index] = maxLength;
//        return maxLength;
//    }
//    else {
//        return getLis(index - 1);
//    }
//}
//
//
//int main(){
//    int_list.push_back(5);
//    int_list.push_back(2);
//    int_list.push_back(3);
//    int_list.push_back(4);
//    int_list.push_back(1);
//    int_list.push_back(2);
//    cache.resize(int_list.size(), -1);
//
//    cout << "the length of longest increasing subsequence is: " << getLis(int_list.size()-1) << endl;
//
//}

int lis(int A[], int n) {
    int *d = new int[n];
    int len = 1;
    for (int i = 0; i < n; ++i) {
        d[i] = 1;
        for (int j = 0; j < i; ++j)
            if (A[j] <= A[i] && d[j] + 1 > d[i])
                d[i] = d[j] + 1;
        if (d[i] > len) len = d[i];
    }
    delete[] d;
    return len;
}

int main() {
    int A[] = {
            5, 3, 4, 8, 6, 7
    };
    cout << lis(A, 6) << endl;
    return 0;
}