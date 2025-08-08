#include <iostream>
#include <algorithm> // 用于max函数
using namespace std;

// AVL树节点结构
struct AVLNode {
    int data;
    AVLNode *lchild, *rchild;
    int height; // 节点高度(以该节点为根的子树高度)
};
typedef AVLNode* AVLTree;

// 获取节点高度(空节点高度为0)
int GetHeight(AVLTree T) {
    return T ? T->height : 0;
}

// 计算平衡因子(右子树高度-左子树高度)
int GetBalanceFactor(AVLTree T) {
    if (!T) return 0;
    return GetHeight(T->lchild) - GetHeight(T->rchild);
}

// 更新节点高度
void UpdateHeight(AVLTree T) {
    if (T) T->height = max(GetHeight(T->lchild), GetHeight(T->rchild)) + 1;
}

// LL平衡旋转(右单旋转)
void LL_Rotation(AVLTree &A) {
    AVLTree B = A->lchild;
    A->lchild = B->rchild;
    B->rchild = A;
    // 更新旋转后节点的高度
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}

// RR平衡旋转(左单旋转)
void RR_Rotation(AVLTree &A) {
    AVLTree B = A->rchild;
    A->rchild = B->lchild;
    B->lchild = A;
    
    // 更新旋转后节点的高度
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}

// LR平衡旋转(先左后右双旋转)
void LR_Rotation(AVLTree &A) {
    RR_Rotation(A->lchild); // 先对A的左孩子进行RR旋转
    LL_Rotation(A); // 再对A进行LL旋转
}

// RL平衡旋转(先右后左双旋转)
void RL_Rotation(AVLTree &A) {
    LL_Rotation(A->rchild); // 先对A的右孩子进行LL旋转
    RR_Rotation(A); // 再对A进行RR旋转
}

// AVL树插入操作
void AVL_Insert(AVLTree &T, int key) {
    // 1. 标准BST插入
    if (!T) { // 找到插入位置，创建新节点
        T = new AVLNode;
        T->data = key;
        T->lchild = T->rchild = NULL;
        T->height = 1; // 新节点高度为1
    	return ;
    }
    
    if (key < T->data) AVL_Insert(T->lchild, key); // 插入左子树
    else if (key > T->data) AVL_Insert(T->rchild, key); // 插入右子树
    else return;// 关键字已存在，不插入
    
    // 2. 更新当前节点高度
    UpdateHeight(T);
    
    // 3. 检查平衡因子，进行相应旋转
    int balance = GetBalanceFactor(T);
    
    // LL型：平衡因子>1且新节点插入左子树的左子树
    if (balance > 1 && key < T->lchild->data) LL_Rotation(T);
    // RR型：平衡因子<-1且新节点插入右子树的右子树
    if (balance < -1 && key > T->rchild->data) RR_Rotation(T);
    // LR型：平衡因子>1且新节点插入左子树的右子树
    if (balance > 1 && key > T->lchild->data) LR_Rotation(T);
    // RL型：平衡因子<-1且新节点插入右子树的左子树
    if (balance < -1 && key < T->rchild->data)RL_Rotation(T);
}

// 查找以T为根的AVL树中的最小节点(用于删除操作)
AVLNode* GetMinNode(AVLTree T) {
    AVLNode *p = T;
    while (p->lchild) p = p->lchild;
    return p;
}

// AVL树删除操作
void AVL_Delete(AVLTree &T, int key) {
    if (!T) return; // 树空或未找到要删除的节点
    
    // 1. 标准BST删除
    if (key < T->data) AVL_Delete(T->lchild, key);
    else if (key > T->data) AVL_Delete(T->rchild, key);
    else { // 找到要删除的节点
        // 情况1: 被删除节点是叶节点(无左右子树)
        if (T->lchild == NULL && T->rchild == NULL) {
            delete T; // 释放节点内存
            T = NULL; // 将父节点指针置空
        }
        // 情况2: 被删除节点只有左子树或右子树
        else if (T->lchild == NULL) { // 只有右子树
            AVLNode *temp = T; // 保存当前节点
            T = T->rchild;     // 右子树替代当前节点
            delete temp;     // 释放内存
        } 
        else if (T->rchild == NULL) { // 只有左子树
            AVLNode *temp = T; // 保存当前节点
            T = T->lchild;     // 左子树替代当前节点
            delete temp;       // 释放内存
        }
        // 情况3: 被删除节点有左右两棵子树
        else {
            // 找到中序后继(右子树最小节点)
            AVLNode *temp = GetMinNode(T->rchild);
            T->data = temp->data;
            // 删除后继节点
            AVL_Delete(T->rchild, temp->data);
        }
    }
    if (!T) return; // 如果树为空，返回
    // 2. 更新当前节点高度
    UpdateHeight(T);
    
    // 3. 检查平衡因子，进行相应旋转
    int balance = GetBalanceFactor(T);
    // LL型：左左情况，右旋
    if (balance > 1 && GetBalanceFactor(T->lchild) >= 0) LL_Rotation(T);
    // RR型：右右情况，左旋
    else if (balance < -1 && GetBalanceFactor(T->rchild) <= 0) RR_Rotation(T);
    // LR型：左右情况，先左旋后右旋
    else if (balance > 1 && GetBalanceFactor(T->lchild) < 0) LR_Rotation(T);
    // RL型：右左情况，先右旋后左旋
    else if (balance < -1 && GetBalanceFactor(T->rchild) > 0) RL_Rotation(T);
}

// AVL树查找操作
int AVL_Search(AVLTree T, int key) {
    if (!T) return 0; // 查找失败
    if (key == T->data) return 1; // 查找成功
    else if (key < T->data) return AVL_Search(T->lchild, key);
    else return AVL_Search(T->rchild, key);
}

// 中序遍历AVL树(递归实现)
void InOrderTraversal(AVLTree T) {
    if (T) {
        InOrderTraversal(T->lchild);
        cout << T->data << "(h=" << T->height << ") ";
        InOrderTraversal(T->rchild);
    }
}
void PreOrderTraversal(AVLTree T) {
    if (T) {
        cout << T->data << "(h=" << T->height << ") ";
        PreOrderTraversal(T->lchild);
        PreOrderTraversal(T->rchild);
    }
}

int main() {
    AVLTree T = NULL;
    int keys[] = {30, 20, 40, 10, 25, 5, 15, 22, 28, 35, 50};
    int n = sizeof(keys) / sizeof(keys[0]);
    
    // 测试插入操作
    cout << "插入序列: \n";
    for (int i = 0; i < n; i++) {
        AVL_Insert(T, keys[i]);
        cout << "先序遍历：";
        PreOrderTraversal(T);
        cout << endl;
        cout << "中序遍历：";
        InOrderTraversal(T);
        cout << endl;
    }
    // 30

    //    30
    //   /
    // 20


    //    30
    //   /  \
    //  20  40

    //     30
    //    /  \
    //   20  40
    //  /
    // 10

    //     30
    //    /  \
    //   20  40
    //  /  \
    // 10  25
    
    //      30                20
    //     /  \              /  \
    //    20  40            10  30
    //   /  \      ->      /    / \
    //  10  25            5    25 40
    //  /
    // 5


    //       20
    //      /  \
    //    10    30
    //    / \  /  \
    //   5  15 25  40
 
    //        20
    //      /     \
    //    10       30
    //    / \     /  \
    //   5  15   25  40
    //          /
    //         22
    
    //        20
    //      /     \
    //    10       30
    //    / \     /  \
    //   5  15   25  40
    //          / \
    //         22 28

    //         20
    //      /      \
    //    10        30
    //    / \     /   \
    //   5  15   25   40
    //          / \   /
    //         22 28 35

    //         20
    //      /      \
    //    10        30
    //    / \     /   \
    //   5  15   25   40
    //          / \   / \
    //         22 28 35 50

    
    cout << "\n中序遍历(带高度): ";
    InOrderTraversal(T);
    cout << endl;
    cout << "前序遍历(带高度): ";
    PreOrderTraversal(T);
    cout << endl;
    
    // 测试查找操作
    int key = 25;
    cout << "查找元素" << key << (AVL_Search(T, key) ? "成功" : "失败") << endl;
    
    // 测试删除操作
    key = 20;
    cout << "删除元素" << key << endl;
    AVL_Delete(T, key);

    
    //         20
    //      /      \
    //    10        30
    //    / \     /   \
    //   5  15   25   40
    //          / \   / \
    //         22 28 35 50


    //         22
    //      /      \
    //    10        30
    //    / \     /   \
    //   5  15   25   40
    //            \   / \
    //            28 35 50

    cout << "删除后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    cout << "删除后前序遍历: ";
    PreOrderTraversal(T);
    cout << endl;
    
    key = 5; 
    cout << "删除元素" << key << endl;
    AVL_Delete(T, key);

    //         22
    //      /      \
    //    10        30
    //    / \     /   \
    //   5  15   25   40
    //            \   / \
    //             28 35 50


    //          22
    //      /       \
    //     10        30       
    //      \     /   \
    //      15   25   40
    //            \   / \
    //            28 35 50
    cout << "删除后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    cout << "删除后前序遍历: ";
    PreOrderTraversal(T);
    cout << endl;

    key = 15; // 删除根节点
    cout << "删除元素" << key << endl;
    AVL_Delete(T, key);
    //          22
    //      /       \
    //     10        30       
    //      \     /   \
    //      15   25   40
    //            \   / \
    //            28 35 50

    //         22                         30   
    //      /      \                    /     \  
    //     10       30                22       40 
    //            /   \              /  \      / \ 
    //           25   40     ->     10   25   35 50    
    //            \   / \                 \ 
    //            28 35 50                28
    cout << "删除后中序遍历: ";
    InOrderTraversal(T);
    cout << endl;
    cout << "删除后前序遍历: ";
    PreOrderTraversal(T);
    cout << endl;
    return 0;
}