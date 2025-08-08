#include <iostream>
#include <queue>

using namespace std;

// 树节点结构定义
struct CTNode {
    int index; // 孩子节点在数组中的位置
    CTNode* next;
};

template <typename T>
struct CTBox {
    T data;
    CTNode* firstchild; // 孩子链表头指针
};

template <typename T>
struct PTree {
    CTBox<T> nodes[100]; // 节点数组
    int n; // 节点数
};

// 先根遍历
void PreOrder(PTree<char>& tree, int index) {
    if (index < 0 || index >= tree.n) return;
    cout << tree.nodes[index].data << " ";
    
    // 遍历孩子链表
    CTNode* child = tree.nodes[index].firstchild;
    while (child) {
        PreOrder(tree, child->index);
        child = child->next;
    }
}

// 后根遍历
void PostOrder(PTree<char>& tree, int index) {
    if (index < 0 || index >= tree.n) return;
    
    // 先遍历孩子节点
    CTNode* child = tree.nodes[index].firstchild;
    while (child) {
        PostOrder(tree, child->index);
        child = child->next;
    }
    
    cout << tree.nodes[index].data << " ";
}

// 层次遍历
void LevelOrder(PTree<char>& tree) {
    if (tree.n == 0) return;
    
    queue<int> q;
    q.push(0); // 根节点在数组中的位置为0
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            int cur = q.front();
            q.pop();
            cout << tree.nodes[cur].data << " ";
            
            // 将当前节点的孩子加入队列
            CTNode* child = tree.nodes[cur].firstchild;
            while (child) {
                q.push(child->index);
                child = child->next;
            }
        }
        cout << endl; // 每层换行
    }
}

// 树形打印辅助函数
void PrintTree(PTree<char>& tree, int index, int level) {
    if (index < 0 || index >= tree.n) return;
    
    // 打印当前节点
    for (int i = 0; i < level; i++)
        cout << "  ";
    cout << "└─" << tree.nodes[index].data << endl;
    
    // 递归打印孩子节点
    CTNode* child = tree.nodes[index].firstchild;
    while (child) {
        PrintTree(tree, child->index, level + 1);
        child = child->next;
    }
}

int main() {
    PTree<char> tree;
    tree.n = 9;
    
    // 初始化节点
    tree.nodes[0] = {'R', nullptr};
    tree.nodes[1] = {'A', nullptr};
    tree.nodes[2] = {'B', nullptr};
    tree.nodes[3] = {'C', nullptr};
    tree.nodes[4] = {'D', nullptr};
    tree.nodes[5] = {'F', nullptr};
    tree.nodes[6] = {'I', nullptr};
    tree.nodes[7] = {'G', nullptr};
    tree.nodes[8] = {'H', nullptr};
    
    // 构建孩子链表
    tree.nodes[0].firstchild = new CTNode{1, new CTNode{2, new CTNode{3, nullptr}}};
    tree.nodes[1].firstchild = new CTNode{4, nullptr};
    tree.nodes[2].firstchild = new CTNode{5, new CTNode{6, nullptr}};
    tree.nodes[5].firstchild = new CTNode{7, new CTNode{8, nullptr}};
    
    // 打印测试信息
    cout << "树形结构：" << endl;

    cout << "树形结构：" << endl;
    PrintTree(tree, 0, 0);

    cout << "\n先根遍历：";
    PreOrder(tree, 0);
    
    cout << "\n\n后根遍历：";
    PostOrder(tree, 0);
    
    cout << "\n\n层次遍历：" << endl;
    LevelOrder(tree);
    
    return 0;
}