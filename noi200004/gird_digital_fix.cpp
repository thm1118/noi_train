/**
 *  双人一起行走，合计最优 ，动规，递归实现 。这是 按单人行走求最优再两人合计 的 修正。
 * */

#include <iostream>
#ifdef LOCAL
#include <fstream>
#endif
#include <vector>
using namespace std;

int n;
// matrix 存放 n 矩阵。maxValuesCache 用来保存已计算后续路径 最大值的点的值
vector<vector<int> > matrix;
vector<vector<vector<vector<int> > > > maxValuesCache;


/** 获取双人同时行，两人所在点的合计最大值*/
int getMaxOfChildren(int row_A, int col_A, int row_B, int col_B){
    if(row_A < 0 || row_B < 0 || col_A < 0 || col_B < 0) return 0;

    // 该坐标点的所有后续路径的最大值是否已经计算过，计算过就取缓存，不重新计算
    if(maxValuesCache[row_A][col_A][row_B][col_B] != -1) return  maxValuesCache[row_A][col_A][row_B][col_B];

    // 返回最大值的同时，缓存该值，下次就不用重新计算了。
    return maxValuesCache[row_A][col_A][row_B][col_B] =
                                            /** 当坐标重合，忽略一个*/
                   matrix[row_A][col_A] + ((row_A == row_B && col_A == col_B)? 0 : matrix[row_B][col_B] )+
                          /** 两个人都来自上面*/
                           max(getMaxOfChildren(row_A - 1, col_A, row_B - 1, col_B) ,
                               /** A 来自上， B 来自左*/
                               max(getMaxOfChildren(row_A-1, col_A, row_B, col_B - 1),
                                   /** A来自左， B 来自 上*/
                                  max(getMaxOfChildren(row_A, col_A - 1, row_B-1, col_B),
                                      /** 两个都来自左*/
                                       getMaxOfChildren(row_A, col_A - 1, row_B, col_B - 1))));
}


int main(){
#ifdef LOCAL
    ifstream fin("grid_digital_fix.in");
    fin >> n;
#else
    cin >>n;
#endif
    // 读取
    matrix = vector<vector<int> >(n, vector<int>(n, 0));
    //保存每个点 后续路径中的的最大值
    maxValuesCache = vector<vector<vector<vector<int> > > >(n, vector<vector<vector<int> > >(n, vector<vector<int> >(n, vector<int>(n, -1))));

    do{
        int row, col, value;
#ifdef LOCAL
        fin >> row >> col >> value;
#else
        cin >> row >> col >> value;
#endif
        if(!row && !col && !value) break;
        matrix[row-1][col-1] = value;
    }while(true);

    int max_value = getMaxOfChildren(n - 1 , n - 1 , n - 1 , n - 1);


#ifdef LOCAL
    cout << "maxvalue: " << max_value <<endl;
    fin.close();
#else
    cout << max_value << endl;
#endif

    return 0;
}
