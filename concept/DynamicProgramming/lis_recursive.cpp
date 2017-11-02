#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> int_list;
vector<int> cache;

int getLis(size_t index){
    if(index == 0) return 1;
    if(cache[index] != -1) return cache[index];

    cache[index] = 1;
    for(int j = 0; j < index; j++ ){
        int jMax =  getLis(j);
        if(int_list[j] < int_list[index]){
            cache[index] = max(cache[index] , jMax + 1);
        }
    }
    return cache[index];
}


int main(){
    int_list.push_back(5);
    int_list.push_back(2);
    int_list.push_back(3);
    int_list.push_back(4);
    int_list.push_back(1);
    int_list.push_back(2);
    cache.resize(int_list.size(), -1);

    getLis(int_list.size()-1);
    sort(cache.begin(),cache.end());

    cout << "the length of longest increasing subsequence is: " << cache[cache.size() -1] << endl;

}