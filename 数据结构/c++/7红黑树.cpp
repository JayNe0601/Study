#include <iostream>
#include <algorithm> // 用于max函数
using namespace std;

// 红黑树节点颜色定义
#define RED 0    // 红色节点
#define BLACK 1  // 黑色节点

// 红黑树节点结构
class RBNode {
public:
    int val;          // 节点值
    bool color;       // 节点颜色
    RBNode *left;     // 左孩子
    RBNode *right;    // 右孩子
    RBNode *parent;   // 父节点

    // 构造函数
    RBNode(int value, bool c, RBNode *p, RBNode *l, RBNode *r) : val(value), color(c), parent(p), left(l), right(r) {}
};

// 红黑树类
class RBTree {
private:
    RBNode *root;       // 根节点
    RBNode *nullNode;   // 哨兵节点，所有空指针指向该节点

    // 左旋转操作
    void leftRotate(RBNode *x) {
        RBNode *y = x->right;  // y是x的右孩子

        // 将y的左子树设为x的右子树
        x->right = y->left;
        if (y->left != nullNode) y->left->parent = x;

        // 将x的父节点设为y的父节点
        y->parent = x->parent;
        if (x->parent == nullNode) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        // 将x设为y的左子树
        y->left = x;
        x->parent = y;
    }

    // 右旋转操作
    void rightRotate(RBNode *y) {
        RBNode *x = y->left;   // x是y的左孩子

        // 将x的右子树设为y的左子树
        y->left = x->right;
        if (x->right != nullNode) x->right->parent = y;

        // 将y的父节点设为x的父节点
        x->parent = y->parent;
        if (y->parent == nullNode) root = x;
        else if (y == y->parent->right) y->parent->right = x;
        else y->parent->left = x;

        // 将y设为x的右子树
        x->right = y;
        y->parent = x;
    }

    // 插入后修复红黑树平衡
    void insertFixup(RBNode *z) {
        // 当父节点为红色时需要修复
        while (z->parent->color == RED) {
            // 父节点是祖父节点的左孩子
            if (z->parent == z->parent->parent->left) {
                RBNode *y = z->parent->parent->right; // 叔叔节点

                // 情况1：叔叔节点为红色
                if (y->color == RED) {
                    z->parent->color = BLACK;         // 父节点设为黑色
                    y->color = BLACK;                  // 叔叔节点设为黑色
                    z->parent->parent->color = RED;    // 祖父节点设为红色
                    z = z->parent->parent;             // 祖父节点成为新的当前节点
                } 
                // 情况2：叔叔节点为黑色，且当前节点是右孩子
                else if (z == z->parent->right) {
                    z = z->parent;                     // 当前节点上移到父节点
                    leftRotate(z);                     // 左旋
                } 
                // 情况3：叔叔节点为黑色，且当前节点是左孩子
                else {
                    z->parent->color = BLACK;         // 父节点设为黑色
                    z->parent->parent->color = RED;    // 祖父节点设为红色
                    rightRotate(z->parent->parent);    // 右旋
                }
            } 
            // 父节点是祖父节点的右孩子（与左孩子情况对称）
            else {
                RBNode *y = z->parent->parent->left;  // 叔叔节点

                // 情况1：叔叔节点为红色
                if (y->color == RED) {
                    z->parent->color = BLACK;         // 父节点设为黑色
                    y->color = BLACK;                  // 叔叔节点设为黑色
                    z->parent->parent->color = RED;    // 祖父节点设为红色
                    z = z->parent->parent;             // 祖父节点成为新的当前节点
                } 
                // 情况2：叔叔节点为黑色，且当前节点是左孩子
                else if (z == z->parent->left) {
                    z = z->parent;                     // 当前节点上移到父节点
                    rightRotate(z);                    // 右旋
                } 
                // 情况3：叔叔节点为黑色，且当前节点是右孩子
                else {
                    z->parent->color = BLACK;         // 父节点设为黑色
                    z->parent->parent->color = RED;    // 祖父节点设为红色
                    leftRotate(z->parent->parent);     // 左旋
                }
            }
        }
        // 确保根节点为黑色
        root->color = BLACK;
    }

    // 删除后修复红黑树平衡
    void deleteFixup(RBNode *x) {
        // 当x不是根节点且为黑色时需要修复
        while (x != root && x->color == BLACK) {
            // x是左孩子
            if (x == x->parent->left) {
                RBNode *w = x->parent->right; // 兄弟节点

                // 情况1：兄弟节点为红色
                if (w->color == RED) {
                    w->color = BLACK;                 // 兄弟节点设为黑色
                    x->parent->color = RED;           // 父节点设为红色
                    leftRotate(x->parent);            // 左旋
                    w = x->parent->right;             // 更新兄弟节点
                }

                // 情况2：兄弟节点为黑色，且两个孩子都为黑色
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;                   // 兄弟节点设为红色
                    x = x->parent;                    // x上移到父节点
                } 
                // 情况3：兄弟节点为黑色，左孩子红色，右孩子黑色
                else if (w->right->color == BLACK) {
                    w->left->color = BLACK;           // 兄弟左孩子设为黑色
                    w->color = RED;                   // 兄弟节点设为红色
                    rightRotate(w);                   // 右旋
                    w = x->parent->right;             // 更新兄弟节点
                } 
                // 情况4：兄弟节点为黑色，右孩子红色
                else {
                    w->color = x->parent->color;      // 兄弟节点颜色设为父节点颜色
                    x->parent->color = BLACK;         // 父节点设为黑色
                    w->right->color = BLACK;          // 兄弟右孩子设为黑色
                    leftRotate(x->parent);            // 左旋
                    x = root;                         // x设为根节点，退出循环
                }
            } 
            // x是右孩子（与左孩子情况对称）
            else {
                RBNode *w = x->parent->left;  // 兄弟节点

                // 情况1：兄弟节点为红色
                if (w->color == RED) {
                    w->color = BLACK;                 // 兄弟节点设为黑色
                    x->parent->color = RED;           // 父节点设为红色
                    rightRotate(x->parent);           // 右旋
                    w = x->parent->left;              // 更新兄弟节点
                }

                // 情况2：兄弟节点为黑色，且两个孩子都为黑色
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;                   // 兄弟节点设为红色
                    x = x->parent;                    // x上移到父节点
                } 
                // 情况3：兄弟节点为黑色，右孩子红色，左孩子黑色
                else if (w->left->color == BLACK) {
                    w->right->color = BLACK;          // 兄弟右孩子设为黑色
                    w->color = RED;                   // 兄弟节点设为红色
                    leftRotate(w);                    // 左旋
                    w = x->parent->left;              // 更新兄弟节点
                } 
                // 情况4：兄弟节点为黑色，左孩子红色
                else {
                    w->color = x->parent->color;      // 兄弟节点颜色设为父节点颜色
                    x->parent->color = BLACK;         // 父节点设为黑色
                    w->left->color = BLACK;           // 兄弟左孩子设为黑色
                    rightRotate(x->parent);           // 右旋
                    x = root;                         // x设为根节点，退出循环
                }
            }
        }
        x->color = BLACK; // 确保x为黑色
    }

    // 中序遍历辅助函数
    void inOrderHelper(RBNode *node) {
        if (node != nullNode) {
            inOrderHelper(node->left);
            cout << node->val << "(" << (node->color ? "黑" : "红") << ") ";
            inOrderHelper(node->right);
        }
    }

    // 查找节点辅助函数
    RBNode* searchHelper(RBNode *node, int key) {
        if (node == nullNode || key == node->val) return node;

        if (key < node->val) return searchHelper(node->left, key);
        else return searchHelper(node->right, key);
    }

    // 查找最小节点
    RBNode* minimum(RBNode *node) {
        while (node->left != nullNode) node = node->left;
        return node;
    }

    // 查找最大节点
    RBNode* maximum(RBNode *node) {
        while (node->right != nullNode) node = node->right;
        return node;
    }

    // 查找后继节点
    RBNode* successor(RBNode *x) {
        if (x->right != nullNode) return minimum(x->right);

        RBNode *y = x->parent;
        while (y != nullNode && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    // 删除节点辅助函数
    void deleteNodeHelper(RBNode *z) {
        RBNode *y = z;       // 将要删除的节点
        RBNode *x;           // y的孩子节点
        bool yOriginalColor = y->color; // y的原始颜色

        // 情况1：z只有右孩子
        if (z->left == nullNode) {
            x = z->right;
            transplant(z, z->right);
        } 
        // 情况2：z只有左孩子
        else if (z->right == nullNode) {
            x = z->left;
            transplant(z, z->left);
        } 
        // 情况3：z有两个孩子
        else {
            y = minimum(z->right); // y是z的后继
            yOriginalColor = y->color;
            x = y->right;

            // 如果y是z的直接右孩子
            if (y->parent == z) x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        // 如果删除的是黑色节点，可能破坏红黑树性质
        if (yOriginalColor == BLACK) deleteFixup(x);

        delete z; // 释放内存
    }

    // 移植操作：用v替换u
    void transplant(RBNode *u, RBNode *v) {
        if (u->parent == nullNode) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

public:
    // 构造函数：初始化红黑树
    RBTree() {
        nullNode = new RBNode(0, BLACK, nullptr, nullptr, nullptr);
        nullNode->left = nullNode->right = nullNode->parent = nullNode;
        root = nullNode;
    }

    // 析构函数：销毁红黑树
    ~RBTree() {
        destroyTree(root);
        delete nullNode;
    }

    // 销毁树辅助函数
    void destroyTree(RBNode *node) {
        if (node != nullNode) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // 中序遍历
    void inOrder() {
        cout << "中序遍历: ";
        inOrderHelper(root);
        cout << endl;
    }

    // 插入节点
    void insert(int key) {
        RBNode *z = new RBNode(key, RED, nullNode, nullNode, nullNode); // 新节点默认为红色
        RBNode *y = nullNode; // 记录父节点
        RBNode *x = root;     // 当前节点

        // 找到插入位置
        while (x != nullNode) {
            y = x;
            if (z->val < x->val) x = x->left;
            else x = x->right;
        }

        z->parent = y;
        if (y == nullNode) root = z;               // 树为空，新节点成为根节点
        else if (z->val < y->val) y->left = z;            // 插入到左子树
        else y->right = z;           // 插入到右子树

        // 如果是根节点，设为黑色
        if (z->parent == nullNode) {
            z->color = BLACK;
            return;
        }

        // 如果祖父节点为空，直接返回
        if (z->parent->parent == nullNode) return;

        // 插入后修复红黑树
        insertFixup(z);
    }

    // 删除节点
    void deleteNode(int key) {
        RBNode *z = search(key);
        if (z != nullNode) deleteNodeHelper(z);
        else cout << "节点" << key << "不存在，无法删除！" << endl;
    }

    // 查找节点
    RBNode* search(int key) {
        return searchHelper(root, key);
    }

    // 获取根节点
    RBNode* getRoot() {
        return root;
    }

    // 打印树结构
    void printTree() {
        cout << "红黑树结构: " << endl;
        printTreeHelper(root, 0);
    }

    // 打印树辅助函数
    void printTreeHelper(RBNode *node, int indent) {
        if (node != nullNode) {
            printTreeHelper(node->right, indent + 4);
            for (int i = 0; i < indent; i++) cout << " ";
            cout << node->val << "(" << (node->color ? "黑" : "红") << ")" << endl;
            printTreeHelper(node->left, indent + 4);
        }
    }
};

// 测试红黑树实现
int main() {
    RBTree tree;

    // 插入测试数据
    int keys[] = {10, 20, 5, 15, 25, 3, 7, 12, 18, 22, 28};
    int n = sizeof(keys) / sizeof(keys[0]);

    cout << "插入节点: ";
    for (int i = 0; i < n; i++) {
        cout << keys[i] << " ";
        tree.insert(keys[i]);
    }
    cout << endl << endl;

    // 显示树结构和遍历结果
    tree.printTree();
    tree.inOrder();
    cout << endl;

    // 测试删除操作
    int deleteKeys[] = {10, 20, 25};
    for (int key : deleteKeys) {
        cout << "删除节点: " << key << endl;
        tree.deleteNode(key);
        tree.printTree();
        tree.inOrder();
        cout << endl;
    }

    // 测试查找操作
    int searchKeys[] = {15, 7, 28, 99};
    for (int key : searchKeys) {
        RBNode *node = tree.search(key);
        // 检查是否为nullNode 
        if (node != tree.getRoot()->left->left->left->left) cout << "查找节点" << key << ": 找到(" << (node->color ? "黑" : "红") << ")" << endl;
        else cout << "查找节点" << key << ": 未找到" << endl;
    }

    return 0;
}