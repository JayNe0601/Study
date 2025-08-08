#include <iostream>
#include <queue>

// 二叉树节点结构体
template<typename T>
struct BiTNode {
    T data;                // 数据域
    BiTNode *lchild, *rchild; // 左右孩子指针
    BiTNode(T val) : data(val), lchild(nullptr), rchild(nullptr) {}// 构造函数
};

/* 初始化空树 */
template<typename T>
void InitTree(BiTNode<T>* &root) {
    root = nullptr;
}

/* 递归创建二叉树 */
template<typename T>
void CreateTree(BiTNode<T>* &root) {
    T val;
    std::cin >> val;
    if(val == '#') return; // #表示空节点
    root = new BiTNode<T>(val);
    CreateTree(root->lchild);
    CreateTree(root->rchild);
}

/* 前序遍历（递归） */
template<typename T>
void PreOrder(BiTNode<T>* root) {
    if(!root) return;
    std::cout << root->data << " ";
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

/* 层次遍历 */
template<typename T>
void LevelOrder(BiTNode<T>* root) {
    if(!root) return;
    std::queue<BiTNode<T>*> q;
    q.push(root);
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        std::cout << node->data << " ";
        
        if(node->lchild) q.push(node->lchild);
        if(node->rchild) q.push(node->rchild);
    }
}

/* 销毁二叉树 */
template<typename T>
void DestroyTree(BiTNode<T>* &root) {
    if(root) {
        DestroyTree(root->lchild);
        DestroyTree(root->rchild);
        delete root;
        root = nullptr;
    }
}

int main() {
    BiTNode<char>* root;
    InitTree(root);
    
    std::cout << "输入先序序列（用#表示空节点）: "; 
    /*
    例如：A B # D # # C F # # E # #
    树为 
        A
     B     C
      D  F   E
    */
    CreateTree(root);
    
    std::cout << "\n前序遍历: ";
    PreOrder(root);
    
    std::cout << "\n层次遍历: ";
    LevelOrder(root);
    
    DestroyTree(root);
    return 0;
}