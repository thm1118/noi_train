#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct NODE {
    // 自身序号
    int name;
    // 观察者 时间
    int observe_time;
    // 指向 唯一的父节点的指针
    NODE *parent = nullptr;
    //指向 子节点指针 的数组，为了可便捷动态大小，使用STL中的vector 容器----动态数组。
    vector<NODE *> children;
};
//  边 的结构定义
struct EDGE {
    int start;
    int end;
};

/**
 *  从节点 向其子节点 递归搜索 目标节点 。返回true，表示找到，false，表示没找到
 * */
bool findNextNode(stack<NODE*> *path, NODE* start, NODE* end) {
    if(start->name == end->name) {
        // 表示找到了
        return true;
    }

    if(start->children.empty()){
        //如果 没有子节点, 说明这条路径没找到
        return false;
    }else{
        for(int i=0; i < start->children.size(); i++){
            if(findNextNode(path, start->children[i], end)) {
                path->push(start->children[i]);
                return true;
            }
        }
        // 子节点都没有
        return false;
    }
}

/**
 *  从节点向上递归搜索 目标节点
 * */
bool findPreNode(stack<NODE*> *path, NODE* start, NODE* end) {
    if(start->name == end->name) {
        // 表示找到了
        return true;
    }
    NODE* parent = start->parent;
    if(parent == nullptr){
        //如果 没有父节点, 那就彻底找不到了
        return false;
    }else{
        // 先把父节点 的所有子节点过一遍，注意排除 来源的start
        for(int i=0; i < parent->children.size(); i++){
            if(parent->children[i]->name != start->name) {
                if (findNextNode(path, parent->children[i], end)) {
                    path->push(parent->children[i]);
                    path->push(parent);
                    return true;
                }
            }
        }
        // 父节点的子节点 都没有，那么就继续往上
        if(findPreNode(path, parent, end)){
            path ->push(parent);
            return true;
        }else{
            return false;
        }
    }
}



/**
 *  测试节点关系
 *  cout 输出中使用了 \t  :表示tab制表符，等同于键盘按下tab键。 endl 表示回车
 * */
void testNodes(int n, NODE nodes[]) {
    int i, j;
    for (i = 0; i < n ; i++) {
        cout << "node:" << nodes[i].name << endl;
        if (nodes[i].parent != nullptr) {
            cout << "\tparent:" << (nodes[i].parent)->name << endl;
        }
        cout << "\tchildren count:" << nodes[i].children.size() << endl;
        for (j = 0; j < nodes[i].children.size(); j++) {
            cout << "\t\tchildren:" << nodes[i].children[j]->name << endl;
        }
    }
};

/**
 *  根据传入 的起始和结束节点 索引，返回路径；
 *  一、关于路径使用何种数据结构的思考：
 *  1、路径是有序的，首先想到数组，因为数组本身自带顺序特征（作为返回值：C++ 函数不允许数组类型的返回值，
 *      需要返回指向数组的 指针，比如NODE*;）；
 *  2、另由于路径大小未知，用vector比 需要预分配空间的数组方便。
 *  3、考虑到路径搜索时，相当于一个一个节点的遍历，需要边遍历边记录节点，如果搜索到，直接返回；
 *      如果遍历到 叶子---即没有子节点的节点，需要返回，并去除无效路径，因此这样的 stack特征，使用STL中的stack 容器
 **/
stack<NODE*> getPath(NODE nodes[], int start_index, int end_index) {
    stack<NODE*> path;

    // 注意这里 本地变量使用指针，这样放进path里最终返回的时候，不会因为是本地变量被销毁而丢失。
    NODE *start = &nodes[start_index - 1];
    NODE *end = &nodes[end_index - 1];

    if(findNextNode(&path, start, end)){
        // 当找到时才记录当前节点到路径中
        path.push(start);
    }else if(findPreNode(&path, start, end)){
        path.push(start);
    }
    return path;
}



int main() {

    /**
     * 1、输入 缓存：定义变量、各种cin，完整加载所有输入内容 到变量
     * */
    // n 个节点 和对应观察员， m个 人
    int n = 6, m = 3;
    int i;
    // 观察者时间
    int observe_time[] = {0, 2, 5, 1, 2, 3};

    // 节点的 边
    struct EDGE edges[] = {
            {2, 3},
            {1, 2},
            {1, 4},
            {4, 5},
            {4, 6}
    };

    /**
     * 2、定义结构
     * */


    /**
     * 3、清洗：转换 数据类型
     * */
    //存放所有节点
    NODE nodes[n];
    //初始化所有节点
    for (i = 0; i < n; i++) {
        NODE node;
        node.name = i + 1;
        node.observe_time = observe_time[i];
        nodes[i] = node;
    };

    //根据 边 初始化节点 关系
    for (i = 0; i < n - 1; i++) {
        EDGE edge = edges[i];
        nodes[edge.end - 1].parent = &nodes[edge.start - 1];
        nodes[edge.start - 1].children.push_back(&nodes[edge.end - 1]);
    }

    /**
     * 4、处理逻辑
     * */
    testNodes(n, nodes);

    stack<NODE*> path = getPath(nodes, 5, 3);

    /**
     * 5、输出，各种cout
     * */
    // 输出 路径
    while(!path.empty()){
        cout<< "node: "<< path.top()->name << endl;
        path.pop();
    }

    /**
     * 6、退出
     * */


    return 0;
}