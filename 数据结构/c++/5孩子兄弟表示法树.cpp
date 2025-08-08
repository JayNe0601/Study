#include <iostream>
#include <queue>
using namespace std;

struct CSNode {
    char data;
    CSNode *firstchild, *nextsibling;
    CSNode(char val) : data(val), firstchild(nullptr), nextsibling(nullptr) {}
};

struct CSTree {
    CSNode* root;
};

void CreateTestTree(CSTree& tree) {
    tree.root = new CSNode('R');
    tree.root->firstchild = new CSNode('A');
    tree.root->firstchild->nextsibling = new CSNode('B');
    tree.root->firstchild->nextsibling->nextsibling = new CSNode('C');
    
    tree.root->firstchild->firstchild = new CSNode('D');
    tree.root->firstchild->nextsibling->firstchild = new CSNode('F');
    tree.root->firstchild->nextsibling->firstchild->nextsibling = new CSNode('I');
}

void PreOrder(CSNode* node) {
    if (!node) return;
    cout << node->data << " ";
    PreOrder(node->firstchild);
    PreOrder(node->nextsibling);
}

void PostOrder(CSNode* node) {
    if (!node) return;
    CSNode* child = node->firstchild;
    while (child) {
        PostOrder(child);
        child = child->nextsibling;
    }
    cout << node->data << " ";
}

void LevelOrder(CSNode* root) {
    if (!root) return;
    queue<CSNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto node = q.front();
            q.pop();
            cout << node->data << " ";
            
            CSNode* child = node->firstchild;
            while (child) {
                q.push(child);
                child = child->nextsibling;
            }
        }
        cout << endl;
    }
}

void PrintTree(CSNode* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++)
        cout << "  ";
    cout << "|" << node->data << endl;
    PrintTree(node->firstchild, level + 1);
    PrintTree(node->nextsibling, level);
}

void DestroyTree(CSNode* node) {
    if (!node) return;
    DestroyTree(node->firstchild);
    DestroyTree(node->nextsibling);
    delete node;
}


int main() {
    CSTree tree;
    CreateTestTree(tree);
    
    cout << "树形结构：" << endl;
    PrintTree(tree.root, 0);
    
    cout << "\n先根遍历：";
    PreOrder(tree.root);
    
    cout << "\n后根遍历：";
    PostOrder(tree.root);
    
    cout << "\n\n层次遍历：" << endl;
    LevelOrder(tree.root);
    
    DestroyTree(tree.root);
    return 0;
}