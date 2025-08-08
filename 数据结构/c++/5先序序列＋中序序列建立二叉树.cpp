#include <iostream>
#include <vector>
using namespace std;

// 二叉树节点结构
template<typename T>
struct TreeNode {
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

/* 根据先序和中序序列构建二叉树 */
template<typename T>
TreeNode<T>* BuildTree(const vector<T>& pre, int pre_start, int pre_end, const vector<T>& in, int in_start, int in_end) {
    if(pre_start > pre_end) return nullptr;
    T root_val = pre[pre_start];
    TreeNode<T>* root = new TreeNode<T>(root_val);
    
    // 在中序序列中定位根节点
    int root_pos = in_start;
    while(root_pos <= in_end && in[root_pos] != root_val) root_pos++;
    
    int left_size = root_pos - in_start;
    
    // 递归构建子树
    root->left = BuildTree(pre, pre_start + 1, pre_start+left_size, in, in_start, root_pos - 1);
    root->right = BuildTree(pre, pre_start+left_size + 1, pre_end, in, root_pos + 1, in_end);
    return root;
}

/* 后序遍历验证树结构 */
template<typename T>
void PrintTree(TreeNode<T>* root) {
    if(!root) {
        cout << '#' << " "; // 空节点用 '#' 表示
        return;
    }
    PrintTree(root->left);
    PrintTree(root->right);
    cout << root->data << " ";
}

/* 释放树内存 */
template<typename T>
void FreeTree(TreeNode<T>* root) {
    if(!root) return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

int main() {
    vector<char> pre = {'A','B','C','D','E','F','G','H','I'};
    vector<char> in = {'B','C','A','E','D','G','H','F','I'};
    
    TreeNode<char>* root = BuildTree(pre, 0, pre.size()-1, in, 0, in.size()-1);
    
    cout << "后序遍历验证: "; // 后序遍历验证: # # # C B # # E # # # H G # # I F D A
    PrintTree(root);
    FreeTree(root);
    return 0;
}