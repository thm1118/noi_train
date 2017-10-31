#include <iostream>
#ifdef LOCAL
#include <fstream>
#endif
#include <vector>
using namespace std;



int n;
// matrix 存放 n 矩阵。maxValuesCache 用来保存已计算后续路径 最大值的点的值
vector<vector<int> > matrix, maxValuesCache;
// NODE结构体 用来定义 路径链表 上的一个节点。包含节点当前对应的matrix的行列坐标，以及下一个节点
struct NODE{
    int row,col;
    NODE *next = NULL;
    // 初始化不存在的行列
    NODE(int x = -1, int y = -1){
        this->row = x;
        this->col = col;
    }
};
// 存放所有可能存在的NODE，这样避免每次都需要创建（还导致需要判断该坐标是否已创建）
vector<vector<NODE> > mRefs;

// 获得当前坐标点 所有后续路径的最大值
int getMaxOfChildren(int row, int col){
    // 该坐标点的所有后续路径的最大值是否已经计算过，计算过就取缓存，不重新计算
    if(maxValuesCache[row][col] != -1) return  maxValuesCache[row][col];
    // 设置对应NODE的 行列
    mRefs[row][col].row = row;
    mRefs[row][col].col = col;

    // 分别 向右 和向左 递归 获取 对应这里两个节点 后续路径的最大值，再 对比取最大。 并设置路径链表。
    // 注意：到最右边，或最下边，没法继续向右或向下了，虚拟个 值-1。
    //    没用0的 原因是，都是0的话，无法分清 是因为实际是0，还是因为 到最右边或最下边获得的0。 -1就能帮助判断哪个分支来的
    // 注意：如果到右下角，那么 就两个都是-1了，会 影响左右的最大值判断，所以在后面 挂接指针的时候，需要判断值是否大于0
    int right_value = (col+1 < n) ? getMaxOfChildren(row, col + 1) : -1;
    int bottom_value = (row + 1) < n ? getMaxOfChildren(row + 1, col): -1;
    int max_value = 0;
    // 大于等于0 ，明确说明不是最右边，并且右值 大于等于下值，则取右边（相等情况下，随便取哪边都行，就约定取右边）
    if(right_value >= 0 && right_value >= bottom_value){
        max_value = right_value;
        mRefs[row][col].next =  &(mRefs[row][col + 1]);
    }else if(bottom_value >= 0 && bottom_value >  right_value){
        // 不是最底部。注意这里 是大于，而不是大于等于。否则会导致。
        // 这个条件看起来多余，但是是有必要的。比如右下角顶点情况。
        max_value = bottom_value;
        mRefs[row][col].next = &(mRefs[row + 1][col]);
    }// 没有else，else 就是顶点 ，max_value 默认就为0.

    // 返回最大值的同时，缓存该值，下次就不用重新计算了。
    return maxValuesCache[row][col] = matrix[row][col] + max_value;
    // 如果不需要记录路径，下面 这一行注释代码就满足提取 后续路径最大值的需求了。
//    return maxValuesCache[row][col] =  matrix[row][col] +
//            max((col+1 < n) ? getMaxOfChildren(row, col+1) : 0, (row + 1) < n ?getMaxOfChildren(row + 1, col): 0);
}

// 清理获得最大值路径链表对应的值。
void clearPath(int row,int col){
#ifdef LOCAL
    cout << row << "," << col << "," << matrix[row][col] << endl;
#endif
    matrix[row][col] = 0;
    if(mRefs[row][col].next != NULL) clearPath(mRefs[row][col].next->row, mRefs[row][col].next->col);
}

void printPath(int row, int col){

    if(mRefs[row][col].next != NULL) printPath(mRefs[row][col].next->row, mRefs[row][col].next->col);
}



int main(){
#ifdef LOCAL
    ifstream fin("grid_digital.in");
    fin >> n;
#endif

#ifndef LOCAL
    cin >>n;
#endif
    // 读取
    matrix = vector<vector<int> >(n, vector<int>(n, 0));
    //保存每个点 后续路径中的的最大值
    maxValuesCache = vector<vector<int> >(n, vector<int>(n, -1));
    //初始化所有NODE, 这样避免每次都需要创建（还导致需要判断该坐标是否已创建）
    mRefs = vector<vector<NODE> >(n, vector<NODE>(n, NODE()));

    do{
        int row, col, value;
#ifdef LOCAL
        fin >> row >> col >> value;
#endif
#ifndef LOCAL
        cin >> row >> col >> value;
#endif
        if(!row && !col && !value) break;
        matrix[row-1][col-1] = value;
    }while(true);

    int max_value1 = getMaxOfChildren(0, 0);

    clearPath(0, 0);

#ifdef LOCAL
    cout << endl;
    clearPath(0, 0);
#endif

    //重置缓存
    maxValuesCache = vector<vector<int> >(n, vector<int>(n, -1));
    int max_value2 = getMaxOfChildren(0, 0);
#ifdef LOCAL
    cout << "maxvalue1: " << max_value1 <<endl;
    cout << "maxvalue2: " << max_value2 <<endl;
    cout << "sum of maxvalue: " << max_value1 + max_value2 << endl;
    fin.close();
#endif
#ifndef LOCAL
    cout << max_value1 + max_value2 << endl;
#endif

    return 0;
}
