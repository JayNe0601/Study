#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template<typename T>
struct TreeNode {
    T data;
    TreeNode *left, *right;
    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

/* 后序+中序构建二叉树 */
template<typename T>
TreeNode<T>* BuildFromPostIn(const vector<T>& post, int post_start, int post_end, const vector<T>& in, int in_start, int in_end) {
    if(post_start > post_end) return nullptr;

    T root_val = post[post_end];
    TreeNode<T>* root = new TreeNode<T>(root_val);

    // 定位中序根节点位置
    int root_pos = in_start;
    while(root_pos <= in_end && in[root_pos] != root_val) root_pos++;

    int left_size = root_pos - in_start;
    int right_size = in_end - root_pos;

    // 递归构建子树
    root->left = BuildFromPostIn(post, post_start, post_start + left_size - 1, in, in_start, root_pos - 1);
    root->right = BuildFromPostIn(post, post_start + left_size, post_end - 1, in, root_pos + 1, in_end);
    return root;
}

/* 层次遍历验证 */
template<typename T>
void LevelOrder(TreeNode<T>* root) {
    if(!root) return;
    queue<TreeNode<T>*> q;
    q.push(root);
    while(!q.empty()) {
        auto node = q.front();
        q.pop();
        cout << node->data << " ";
        if(node->left) q.push(node->left);
        if(node->right) q.push(node->right);
    }
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
    vector<char> post = {'C','B','E','H','G','I','F','D','A'};
    vector<char> in = {'B','C','A','E','D','G','H','F','I'};
    
    TreeNode<char>* root = BuildFromPostIn(post, 0, post.size() - 1, in, 0, in.size() - 1);
    
    cout << "层次遍历验证: ";// A B D C E F G I H
    LevelOrder(root);
    
    FreeTree(root);
    return 0;
}