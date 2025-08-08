#include <iostream>
using namespace std;

#define MAX 100

struct BSTNode {
    int data;
    BSTNode *lchild, *rchild;
};
typedef BSTNode *BSTTree;

int a[MAX];
int length = 0;

// 中序遍历二叉排序树(递归实现)
void InOrderTraversal(BSTTree T) {
    if (T != NULL) {
        InOrderTraversal(T->lchild);
        cout << T->data << " ";
        InOrderTraversal(T->rchild);
    }
}

// 插入节点到二叉排序树
void BST_Insert(BSTTree &T, int key) {
    if (T == NULL) {
        T = new BSTNode;
        T->data = key;
        T->lchild = T->rchild = NULL;
    }
    else if (key < T->data) BST_Insert(T->lchild, key);
    else if (key > T->data) BST_Insert(T->rchild, key);
    else cout << "二叉排序树中已存在相同关键字的节点，插入失败!" << endl;
}

// 创建二叉排序树
void Create_BST(BSTTree &T) {
    T = NULL; // 初始化为空树
    for (int i = 0; i < length; i++) BST_Insert(T, a[i]);
}

// 二叉排序树查找(非递归实现)
int BST_Search(BSTTree T, int key) {
    if (T == NULL) return 0; // 查找失败
    BSTTree p = T;
    while (p != NULL) {
        if (key == p->data) return 1; // 查找成功
        else if (key < p->data) p = p->lchild; // 向左查找
        else p = p->rchild; // 向右查找
    }
    return 0; // 查找失败
}

// 查找以T为根的二叉排序树中的最小节点(用于寻找直接后继)
BSTNode* GetMinNode(BSTTree T) {
    BSTNode *p = T;
    while (p->lchild != NULL) p = p->lchild;
    return p;
}

// 二叉排序树删除操作
void BST_Delete(BSTTree &T, int key) {
    if (T == NULL) return; // 树空，无需删除
    if (key < T->data) BST_Delete(T->lchild, key); // 递归删除左子树
    else if (key > T->data) BST_Delete(T->rchild, key); // 递归删除右子树
    else { // 找到要删除的节点
        // 情况1: 被删除节点是叶节点(无左右子树)
        if (T->lchild == NULL && T->rchild == NULL) {
            delete T; // 释放节点内存
            T = NULL; // 将父节点指针置空
        }
        // 情况2: 被删除节点只有左子树或右子树
        else if (T->lchild == NULL) { // 只有右子树
            BSTNode *temp = T; // 保存当前节点
            T = T->rchild;     // 右子树替代当前节点
            delete temp;     // 释放内存
        } 
        else if (T->rchild == NULL) { // 只有左子树
            BSTNode *temp = T; // 保存当前节点
            T = T->lchild;     // 左子树替代当前节点
            delete temp;       // 释放内存
        }
        // 情况3: 被删除节点有左右两棵子树
        else {
            // 找直接后继(右子树中最小节点)
            BSTNode *temp = GetMinNode(T->rchild);
            T->data = temp->data; // 用后继节点值替换当前节点值
            BST_Delete(T->rchild, temp->data); // 递归删除后继节点
        }
    }
}

void PreOrder(BSTTree T) {
    if (T != NULL) {
        cout << T->data << " ";
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

int main() {
    // 初始化测试数据
    int sortedData[] = {53, 17, 9, 45, 78, 65, 94, 23, 81, 88};
    length = sizeof(sortedData) / sizeof(sortedData[0]);
    for(int i = 0; i < length; i++) a[i] = sortedData[i];

    // 创建二叉排序树
    BSTTree T;
    Create_BST(T);

    // 中序遍历BST(应输出排序结果)
    cout << "中序遍历二叉排序树: ";
    InOrderTraversal(T);
    cout << endl;

    // 测试查找功能
    int key = 34;
    cout << "查找元素" << key << (BST_Search(T, key) ? "成功" : "失败") << endl;
    
    key = 88;
    cout << "查找元素" << key << (BST_Search(T, key) ? "成功" : "失败") << endl;

    // 测试删除功能
    cout << "\n原始二叉排序树中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    
    // 情况1: 删除有左右子树的节点(78)
    BST_Delete(T, 78);
    cout << "删除有左右子树的节点78后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    
    cout << "删除有左右子树的节点78后前序遍历: ";
    PreOrder(T);
    cout << endl;
    
    // 情况2: 删除只有左子树的节点(45)
    BST_Delete(T, 45);
    cout << "删除只有左子树的节点45后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    
    cout << "删除只有左子树的节点45后前序遍历: ";
    PreOrder(T);
    cout << endl;
    

    // 情况3: 删除叶子节点的节点(23)
    BST_Delete(T, 23);
    cout << "删除叶子节点的节点23后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;

    cout << "删除叶子节点的节点23后前序遍历: ";
    PreOrder(T);
    cout << endl;

    return 0;
}