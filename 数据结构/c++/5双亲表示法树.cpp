#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct PTree {
    int num_nodes;
    struct Node {
        char data;
        int parent;
    } nodes[100];
};

// 先根遍历
void PreOrder(const PTree& tree, int index) {
    if(index == -1) return;
    cout << tree.nodes[index].data << " ";
    for(int i = 0; i < tree.num_nodes; i++) if(tree.nodes[i].parent == index) PreOrder(tree, i);
}

// 后根遍历
void PostOrder(const PTree& tree, int index) {
    if(index == -1) return;
    for(int i = 0; i < tree.num_nodes; i++) if(tree.nodes[i].parent == index) PostOrder(tree, i);
    cout << tree.nodes[index].data << " ";
}

// 层次遍历
void LevelOrder(const PTree& tree) {
    queue<int> q;
    q.push(0); // 根节点位置为0
    
    while(!q.empty()) {
        int size = q.size();
        for(int i = 0; i < size; i++) {
            int cur = q.front();
            q.pop();
            cout << tree.nodes[cur].data << " ";
            // 查找所有子节点
            for(int j = 0; j < tree.num_nodes; j++) if(tree.nodes[j].parent == cur) q.push(j);
        }
    }
}

// 树形打印辅助函数
void PrintTree(const PTree& tree, int index, int level) {
    if(index == -1) return;
    for(int i = 0; i < level; i++) cout << "  ";
    cout << "└─" << tree.nodes[index].data << endl;
    for(int i = 0; i < tree.num_nodes; i++)
        if(tree.nodes[i].parent == index)
            PrintTree(tree, i, level + 1);
}

int main() {
    PTree tree;
    tree.num_nodes = 10;
    tree.nodes[0] = {'R', -1};
    tree.nodes[1] = {'A', 0};
    tree.nodes[2] = {'B', 0};
    tree.nodes[3] = {'C', 0};
    tree.nodes[4] = {'D', 1};
    tree.nodes[5] = {'E', 1};
    tree.nodes[6] = {'F', 3};
    tree.nodes[7] = {'G', 6};
    tree.nodes[8] = {'H', 6};
    tree.nodes[9] = {'I', 6};

    cout << "树形结构：" << endl;
    PrintTree(tree, 0, 0);

    cout << "先根遍历：" << endl;
    PreOrder(tree, 0);

    cout << "\n后根遍历：" << endl;
    PostOrder(tree, 0);
    
    cout << "\n层次遍历：" << endl;
    LevelOrder(tree);
    return 0;
}