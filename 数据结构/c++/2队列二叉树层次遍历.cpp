#include <iostream>
#include <queue>
using namespace std;

typedef struct BiTNode {
    char data;
    BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 创建二叉树
void CreateTree(BiTree &T) {
    char ch;
    cin >> ch;
    if (ch == '#') T = nullptr;
    else {
        T = new BiTNode;
        T->data = ch;
        CreateTree(T->lchild);
        CreateTree(T->rchild);
    }
}

// 层次遍历核心算法
void LevelOrder(BiTree T) {
    if (!T) return;
    queue<BiTNode*> Q;
    Q.push(T);
    
    while (!Q.empty()) {
        int levelSize = Q.size();
        for (int i = 0; i < levelSize; i++) {
            BiTNode* node = Q.front();
            Q.pop();
            cout << node->data << " ";
            
            if (node->lchild) Q.push(node->lchild);
            if (node->rchild) Q.push(node->rchild);
        }
        cout << "| "; // 层级分隔符
    }
}


// 添加内存释放函数
void DestroyTree(BiTree &T) {
    if (T) {
        DestroyTree(T->lchild);
        DestroyTree(T->rchild);
        delete T;
        T = nullptr;
    }
}

// 更新测试用例
int main() {
    BiTree T;
    cout << "输入先序序列(例:ABD##E##CF##G##): ";
    CreateTree(T);
    
    cout << "层次遍历结果: ";
    LevelOrder(T);
    
    // 空树测试
    cout << "\n空树测试: ";
    LevelOrder(nullptr);
    
    DestroyTree(T);
    system("pause");
    return 0;
}