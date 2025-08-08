#include <iostream>
using namespace std;

typedef struct LinkNode {
    int data;
    LinkNode* next;
} *LiStack;

// 初始化链栈
bool InitStack(LiStack &S) {
    S = nullptr;
    return true;
}

// 判断栈空
bool StackEmpty(LiStack S) {
    return S == nullptr;
}

// 入栈操作
bool Push(LiStack &S, int x) {
    LinkNode* newNode = new LinkNode{x, S};
    S = newNode;
    return true;
}

// 出栈操作
bool Pop(LiStack &S, int &x) {
    if (StackEmpty(S)) {
        cout << "\033[33m空栈警告\033[0m" << endl;
        return false;
    }
    LinkNode* delNode = S;
    x = S->data;
    S = S->next;
    delete delNode;
    return true;
}

// 获取栈顶元素
bool GetTop(LiStack S, int &x) {
    if (StackEmpty(S)) {
        cout << "\033[33m空栈警告\033[0m" << endl;
        return false;
    }
    x = S->data;
    return true;
}

// 销毁栈
void DestroyStack(LiStack &S) {
    while (S) {
        LinkNode* temp = S;
        S = S->next;
        delete temp;
    }
}

// 测试用例
int main() {
    LiStack S;
    InitStack(S);

    // 测试入栈
    for (int i = 1; i <= 5; i++) if (!Push(S, i * 10)) break;

    // 测试获取栈顶
    int top;
    GetTop(S, top);
    cout << "当前栈顶: " << top << endl;

    // 测试出栈
    int x;
    while (!StackEmpty(S)) {
        Pop(S, x);
        cout << "弹出元素: " << x << endl;
    }

    DestroyStack(S);
    return 0;
}