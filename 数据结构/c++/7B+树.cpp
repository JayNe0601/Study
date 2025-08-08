#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

/**
 * B+树实现：多路平衡查找树
 * 特点：
 * 1. 所有关键字都存储在叶子节点，形成有序链表
 * 2. 非叶子节点只存储索引，不存储实际数据
 * 3. 支持范围查询和随机查询
 */

// B+树常量定义
const int M = 4;        // B+树的阶数
const int MM = 2 * M;   // 非叶子节点最大关键字数 = 2*M
const int L = 5;        // 叶节点能容纳的最大键值对数

/**
 * B+树节点结构
 * 分为叶子节点和非叶子节点两种类型
 */
struct Node {
    bool leaf;              // 是否为叶节点
    Node* parent;           // 父节点指针
    Node* children[MM + 1]; // 子节点指针数组
    int values[MM];         // 关键字数组
    int cnt;                // 当前关键字数量
};

/**
 * B+树类
 * 实现B+树的插入、显示等基本操作
 */
class BPlusTree {
public:
    BPlusTree();            // 构造函数
    ~BPlusTree();           // 析构函数
    void insert(int value); // 插入记录
    void show();            // 显示整棵B+树

private:
    /**
     * 对满节点进行分裂
     * @param x 父节点
     * @param idx 需要分裂的子节点索引
     */
    void split(Node* x, int idx);

    /**
     * 向非满节点插入关键字
     * @param x 目标节点
     * @param value 待插入关键字
     */
    void insertNonfull(Node* x, int value);

    /**
     * 递归显示节点及其子树
     * @param x 当前节点
     * @param num 当前层级
     */
    void show(Node* x, int num);

    Node* root; // 根节点指针
};

/**
 * B+树构造函数
 * 初始化空树
 */
BPlusTree::BPlusTree() {
    root = NULL;
}

/**
 * B+树析构函数
 * TODO: 实现节点内存释放
 */
BPlusTree::~BPlusTree() {
    // TODO
}

/**
 * 分裂满节点
 * 1. 创建新节点y
 * 2. 将z节点的后L个关键字移动到y节点
 * 3. 更新父节点x的关键字和子节点指针
 * @param x 父节点
 * @param idx 需要分裂的子节点索引
 */
void BPlusTree::split(Node* x, int idx) {
    Node* y = new Node();
    Node* z = x->children[idx];
    y->leaf = z->leaf;
    y->cnt = L;
    z->cnt = L;

    // 将z节点的后L个值移动到y节点
    memcpy(y->values, z->values + L, sizeof(int) * L);

    // 如果不是叶子节点，复制子节点指针
    if(!y->leaf) {
        memcpy(y->children, z->children + L, sizeof(Node*) * (L + 1));
        for(int i = L; i < MM; i++) z->children[i] = NULL;
    }
    z->cnt = L;

    // 为父节点x插入键值，并将y节点加入到x的子节点中
    for(int i = x->cnt + 1; i > idx + 1; i--) x->children[i] = x->children[i - 1];
    x->children[idx + 1] = y;
    for(int i = x->cnt; i > idx; i--) x->values[i] = x->values[i - 1];
    x->values[idx] = z->values[L];
    x->cnt++;
}

/**
 * 向非满节点插入关键字
 * 1. 叶子节点：直接插入并保持有序
 * 2. 非叶子节点：找到合适的子节点，递归插入
 * @param x 目标节点
 * @param value 待插入关键字
 */
void BPlusTree::insertNonfull(Node* x, int value) {
    int i = x->cnt - 1;

    if(x->leaf) {
        // 叶子节点：从后向前找到插入位置
        while(i >= 0 && value < x->values[i]) {
            x->values[i + 1] = x->values[i];
            i--;
        }
        x->values[i + 1] = value;
        x->cnt++;
    }
    else {
        // 非叶子节点：找到对应的子节点
        while(i >= 0 && value < x->values[i]) i--;
        i++;

        // 如果子节点已满，先分裂
        if(x->children[i]->cnt == MM) {
            split(x, i);
            if(value > x->values[i]) i++;
        }
        insertNonfull(x->children[i], value);
    }
}

/**
 * 插入关键字到B+树
 * 1. 空树：创建根节点
 * 2. 根节点满：创建新根节点，分裂原根节点
 * 3. 递归插入到合适位置
 * @param value 待插入关键字
 */
void BPlusTree::insert(int value) {
    if(root == NULL) {
        // 空树，创建根节点（初始为叶子节点）
        root = new Node();
        root->leaf = true;
        root->cnt = 1;
        root->values[0] = value;
    }
    else {
        // 根节点满，需要分裂
        if(root->cnt == MM) {
            Node* s = new Node();
            s->leaf = false;
            s->children[0] = root;
            split(s, 0);
            root = s;
            // 确定插入到哪个子节点
            if(value > root->values[0]) insertNonfull(root->children[1], value);
            else insertNonfull(root->children[0], value);
        }
        else {
            insertNonfull(root, value);
        }
    }
}

/**
 * 显示B+树结构
 * 从根节点开始递归显示
 */
void BPlusTree::show() {
    if(root != NULL) show(root, 0);
}

/**
 * 递归显示节点及其子树
 * @param x 当前节点
 * @param num 当前层级（根节点为0）
 */
void BPlusTree::show(Node* x, int num) {
    cout << "(" << num << ")"; // 显示层级
    for(int i = 0; i < x->cnt; i++) cout << x->values[i] << " ";
    cout << endl;

    // 如果不是叶子节点，递归显示所有子节点
    if(!x->leaf) 
        for(int i = 0; i <= x->cnt; i++) 
            if(x->children[i] != NULL) 
                show(x->children[i], num + 1);
}

/**
 * 主函数：B+树测试
 * 功能：
 * 1. 创建B+树实例
 * 2. 插入20个测试数据
 * 3. 显示树结构
 */
int main() {
    BPlusTree tree;
    for(int i = 0; i < 20; i++) tree.insert(i);
    tree.show();
    return 0;
}