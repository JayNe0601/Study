#include <iostream>
using namespace std;

// 线索树节点定义
template<typename T>
struct ThreadTreeNode {
    T data;
    ThreadTreeNode *left, *right;
    int ltag, rtag; // 0:孩子 1:线索
    ThreadTreeNode(T val) : data(val), left(nullptr), right(nullptr), ltag(0), rtag(0) {}
};

using ThreadTree = ThreadTreeNode<char>*;

// 中序线索化递归辅助
void InThread(ThreadTree &p, ThreadTree &pre) {
    if(p) {
        InThread(p->left, pre);
        
        // 左线索化
        if(!p->left) {
            p->left = pre;
            p->ltag = 1;
        }
        
        // 前驱右线索
        if(pre && !pre->right) {
            pre->right = p;
            pre->rtag = 1;
        }
        
        pre = p;
        InThread(p->right, pre);
    }
}

// 创建中序线索二叉树
void CreateInThread(ThreadTree T) {
    ThreadTree pre = nullptr;
    if(T) {
        InThread(T, pre);
        pre->right = nullptr; // 最后节点的后继置空
        pre->rtag = 1;
    }
}

// 中序线索遍历
// 查找右子树最左下节点
ThreadTree FindLeftMost(ThreadTree node) {
    if(!node) return nullptr;
    while(node->ltag == 0 && node->left) node = node->left;
    return node;
}

ThreadTree NextNode(ThreadTree node) {
    if(!node) return nullptr;
    if(node->rtag == 1) return node->right;
    return FindLeftMost(node->right);
}

void InOrder(ThreadTree T) {
    for(ThreadTree p = FindLeftMost(T); p; p = NextNode(p)) cout << p->data << " ";
}

// 测试用例
int main() {
    /* 创建测试树
          A
        /   \
       B     C
      / \   /
     D  E  F
    */
    ThreadTree root = new ThreadTreeNode<char>('A');
    root->left = new ThreadTreeNode<char>('B');
    root->right = new ThreadTreeNode<char>('C');
    root->left->left = new ThreadTreeNode<char>('D');
    root->left->right = new ThreadTreeNode<char>('E');
    root->right->left = new ThreadTreeNode<char>('F');
    
    CreateInThread(root);
    
    cout << "中序线索遍历结果: ";
    InOrder(root); // 应输出 D B E A F C
    
    return 0;
}
