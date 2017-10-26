#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;


/**
 * 定义结构
 * */
struct NODE {
    // 自身序号
    int name;
    // 观察者 时间
    int observe_time;
    //实际观察人数
    int times;
    // 指向 唯一的父节点的指针
    NODE *parent = NULL;
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
    if(parent == NULL){
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
        if (nodes[i].parent != NULL) {
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

/**
 * 读取输入流 到 指定的数据结构中
 * */
void readInput(ifstream &fin, int n, int m,   EDGE *edges,  int *observe_time,  EDGE *start_end) {
    int i;
    for (i = 0; i < n - 1; i++) {
        fin >> edges[i].start >> edges[i].end;
    }
    for (i = 0; i < n; i++) {
        fin >> observe_time[i];
    }
    for (i = 0; i < m; i++) {
        fin >> start_end[i].start >> start_end[i].end;
    }
}

/**
 *  初始化节点，以及节点的 父子关系
 * */
void initNodes(int n, const EDGE *edges, const int *observe_time, NODE *nodes) {
    int i;
    //初始化所有节点
    for (i = 0; i < n; i++) {
            NODE node;
            node.name = i + 1;
            node.times = 0;
            node.observe_time = observe_time[i];
            nodes[i] = node;
        };

    //根据 边 初始化节点 关系
    for (i = 0; i < n - 1; i++) {
            EDGE edge = edges[i];
            nodes[edge.end - 1].parent = &nodes[edge.start - 1];
            nodes[edge.start - 1].children.push_back(&nodes[edge.end - 1]);
        }
}

/**
 *  输出观察次数到文件
 * */
void outputToFile(ofstream &fout, int n, const NODE *nodes) {
    int i;
    for (i = 0; i < n; i++) {
            fout << nodes[i].times;
            // 这样是为了 让最后一个输出后面不是空格，而是回车
            if (i < n - 1) {
                fout << " ";
            } else {
                fout << endl;
            }
        }
}

int main() {
    /**
     * 1、声明 文件输入输出流
     * */
    // 这里是因为cmake编译后文件在子目录下，todo： 比赛环节应该如何做？是指定文件名，还是通过main参数引入？
    ifstream fin("./../data.in");
    ofstream fout("./../data.out");

    if(fin.fail() )
    {
        cout << "打开文件失败---- 这个判断应不需要"<<endl;
        return 1;
    }

    do {
        /**
        * 2、定义用来保存输入的 变量； 完整加载一组数据 的所有输入内容 到变量
        * */
        // n代表树的结点数量，同时也是观察员的数量， m代表玩家的数量
        int n, m, i;
        fin >> n >> m;

        //保存所有边的数组。两个整数u和v，表示结点u到结点v有一条边
        EDGE edges[n - 1];
        // n个整数，其中第j个整数为Wj，表示结点j出现观察员的时间
        int observe_time[n];
        //m行，每行两个整数Si和Ti，表示一个玩家的起点和终点 。由于结构和EGGE一致，所有也用EDGE
        EDGE start_end[m];
        // 读取输入流 到上面声明的 输入数据中
        readInput(fin, n, m, edges, observe_time, start_end);

        /**
         * 3、清洗：转换 数据类型 为 符合处理算法需要的数据结构： 用NODE 结构体来描述 树形结构的 一个节点
         * */
        //存放所有节点
        NODE nodes[n];
        //初始化节点，以及节点的 父子关系
        initNodes(n, edges, observe_time, nodes);

        /**
         * 4、处理逻辑
         * */
        testNodes(n, nodes);

        for (i = 0; i < m; i++) {
            stack<NODE *> path = getPath(nodes, start_end[i].start, start_end[i].end);
            int count = 0;
            // 根据路径 判断 节点观察到的人数
            while (!path.empty()) {
                // 输出 路径。 注意竞赛不能输出
                cout << "node: " << path.top()->name << " - >";
                if (path.top()->observe_time == count) {
                    path.top()->times++;
                }
                path.pop();
                count++;
            }
            cout << endl;
        }

        /**
         * 5、输出： 输出观察次数到文件. todo： 这样输出是否赛题要求？
         * */
        outputToFile(fout, n, nodes);

    }while(!fin.eof());
    /**
     * 6、退出
     * */

    // 不要忘了关闭流
    // 需要竞赛环境 支持多组数据传入，这样就应该在退出前关闭
    fin.close();
    fout.close();
    return 0;
}