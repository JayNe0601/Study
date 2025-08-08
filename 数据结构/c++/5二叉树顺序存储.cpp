#include <iostream>
#include <string>

const int MAX_SIZE = 100; // 二叉树最大节点容量

/* 顺序存储二叉树结构体 */
template<typename T> // 模板类，T 为数据类型
struct SeqBiTree {
    T data[MAX_SIZE];     // 存储数组
    int size = 0;         // 当前节点数量
    bool isEmpty() { return size == 0; } // 判空方法
};

/* 初始化空二叉树 */
template<typename T>
void InitTree(SeqBiTree<T> &tree) {
    tree.size = 0;
}

/* 根据层次遍历序列创建二叉树 */
template<typename T>
void CreateTree(SeqBiTree<T> &tree, const T* arr, int len) {
    for(int i = 0; i < len && i < MAX_SIZE; ++i) {
        tree.data[i] = arr[i];
        tree.size++;
    }
}

/* 获取父节点索引 */
template<typename T>
int Parent(const SeqBiTree<T> &tree, int i) {
    if(i <= 0 || i >= tree.size) return -1;
    return (i - 1) / 2; // 完全二叉树父节点公式
}

/* 前序遍历（递归辅助函数） */
template<typename T>
void PreOrder(const SeqBiTree<T> &tree, int i) {
    if(i >= tree.size || tree.data[i] == ' ') return;// 空节点返回
    std::cout << tree.data[i] << " ";
    PreOrder(tree, 2 * i + 1); // 左孩子
    PreOrder(tree, 2 * i + 2); // 右孩子
}

/* 层次遍历 */
template<typename T>
void LevelOrder(const SeqBiTree<T> &tree) {
    for(int i = 0; i < tree.size; ++i) {
        if(tree.data[i] == ' ') continue;// 空节点跳过
        std::cout << tree.data[i] << " ";
    }
}

int main() {
    SeqBiTree<char> tree;
    InitTree(tree);

    // 创建测试二叉树
    char levelOrder[] = {'A','B','C',' ','D','E','F'};
    /*
    二叉树结构:
         A
       B   C
        D E F
    */
    CreateTree(tree, levelOrder, 7);

    std::cout << "前序遍历: ";
    PreOrder(tree, 0);
    std::cout << "\n层次遍历: ";
    LevelOrder(tree);

    return 0;
}