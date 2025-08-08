#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

template<typename T>
struct TreeNode {
    T data;
    TreeNode *left, *right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

/* 核心构建函数 */
template<typename T>
TreeNode<T>* BuildTree(const vector<T>& level, const vector<T>& in) {
    if(level.empty() || in.empty()) return nullptr;
    
    T rootVal = level[0];
    TreeNode<T>* root = new TreeNode<T>(rootVal);
    
    auto rootPos = find(in.begin(), in.end(), rootVal);
    vector<T> leftIn(in.begin(), rootPos);
    vector<T> rightIn(rootPos + 1, in.end());
    
    vector<T> leftLevel, rightLevel;
    for(const auto& val : level) {
        if(find(leftIn.begin(), leftIn.end(), val) != leftIn.end()) leftLevel.push_back(val);
        if(find(rightIn.begin(), rightIn.end(), val) != rightIn.end()) rightLevel.push_back(val);
    }
    root->left = BuildTree(leftLevel, leftIn);
    root->right = BuildTree(rightLevel, rightIn);
    return root;
}


/* 前序遍历验证 */
template<typename T>
void PreOrder(TreeNode<T>* root) {
    if(!root) {
        cout << "# ";
        return;
    }
    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

/* 内存释放 */
template<typename T>
void FreeTree(TreeNode<T>* root) {
    if(!root) return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

int main() {
    vector<char> level = {'A','B','D','C','E','F','G','I','H'};
    vector<char> in = {'B','C','A','E','D','G','H','F','I'};
    
    TreeNode<char>* root = BuildTree(level, in);
    
    cout << "前序遍历验证: ";
    PreOrder(root);  // 应输出：A B # C # # D E # # F G # H # # I # #
    
    FreeTree(root);
    return 0;
}